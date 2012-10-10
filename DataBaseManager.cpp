#include "DataBaseManager.h"
#include <qfile.h>
#include <qtextstream.h>

DataBaseManager::DataBaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("MLPDatabase.sqlite");
    if(!db.open())
    {
        QMessageBox mb;
        mb.setText("Database kann nicht geöffnet werden.");
        mb.exec();
    }

    query = new QSqlQuery(db);

    initializeFirst();
}

DataBaseManager::DataBaseManager(const DataBaseManager& dataBaseManager)
{
    this->db.cloneDatabase(dataBaseManager.db, dataBaseManager.db.connectionName());
    query = new QSqlQuery(db);
}

DataBaseManager::~DataBaseManager()
{
    db.close();
}

void DataBaseManager::initializeFirst()
{
    query->exec("CREATE TABLE Farms(Nr, 'Name')");
}

QSqlDatabase DataBaseManager::getSQLDatabase()
{
    return db;
}

void DataBaseManager::executeQuery(const QString& aQuery)
{
    query->exec(aQuery);
}

void DataBaseManager::createTable(const QString& tableName, QVector<QString> attributes)
{
    QString statement(tableName);
    for(int i = 0; i < attributes.size(); i++)
        statement +=attributes[i];
    query->exec(statement);
}

bool inputFromFile(QString filename)
{
    //StringLength of the eventnumber in the file (positions 3-8 each Line)
    //adding the Length of the first 2 Positions (VN,..)
    int eventNbLen = 8;
    //Len of senseless value properties (1-8), 9+10 =: valLen, 11 = scale
    int senseLessLen = 8;

    //Final array (Cows x Values)
    QMap<QString, QList<QString> > cow;
    //Farm-nb. -> NOT INTEGER (caused by occurable leading zeros)
    QString farmNb;


    //String length of the next read values, length of the scale
    int vLen[20];
    int scale[20];
    //Number of values in the next definition
    int vCount = 0;

    //load file
    QFile MLPData(filename);
    if (!MLPData.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream stream(&MLPData);
    QString line;

    /////////////////////////////
    //     Getting FarmNb      //
    /////////////////////////////

    //first line of the file and skip to the first definition
    line = stream.readLine();
    while((line.at(0) != 'D')||(line.at(1) != 'N'))
        line = stream.readLine();
    //set length of the Farm-nb.
    vLen[0] = (line.mid(eventNbLen+senseLessLen,2)).toInt();
    //skip to the real value
    while((line.at(0) != 'V')||(line.at(1) != 'N'))
        line = stream.readLine();

    //NOT INTEGER (caused by occurable leading zeros)
    farmNb = line.mid(senseLessLen,vLen[0]);
    //delete leading spaces
    int i = 0;
    while ((i < farmNb.length())&&(farmNb.at(i) == ' '))i++;
    farmNb = farmNb.mid(i,farmNb.length()-i);

    /////////////////////////////////////
    //     Getting Cow Properties      //
    /////////////////////////////////////

    //skip to the next definition
    while((line.at(0) != 'D')||(line.at(1) != 'N'))
        line = stream.readLine();
    //read definition
    i = eventNbLen+senseLessLen;
    while(i<line.length())
    {
        vLen[vCount] = (line.mid(i,2)).toInt();
        scale[vCount] = (line.mid(i+2,1)).toInt();
        vCount++;
        i += senseLessLen+3;
    }

    ///SCHLEIFE????

    //skip to the next line of values
    while((line.at(0) != 'V')||(line.at(1) != 'N'))
        line = stream.readLine();

    i = eventNbLen + vLen[0];
    //read values
    for(int k=1;k<vCount;k++)
    {
        cow[line.mid(eventNbLen,vLen[0])].push_back(line.mid(i,vLen[k]));
        i += vLen[k];
    }

    MLPData.close();
}

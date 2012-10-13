#include "DataBaseManager.h"
#include <qfile.h>
#include <qtextstream.h>
#include <qmath.h>

#include<QMap>
#include<QString>

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
    query->exec("CREATE TABLE IF NOT EXISTS farms("
                "id nvarchar(10), "
                "name nvarchar(20), "
                "lastname nvarchar(20), "
                "firstname nvarchar(20), "
                "street nvarchar(100), "
                "PLZ nvarchar(5), "
                "city nvarchar(30), "
                "tel nvarchar(20), "
                "fax nvarchar(20), "
                "hint nvarchar(255), "
                "createdate nvarchar(10), "
                "changedate nvarchar(10), "
                "PRIMARY KEY(id))");

    query->exec("CREATE TABLE IF NOT EXISTS cows ("
                "lifenb nvarchar(20), "
                "cowname nvarchar(10), "
                "cownb INTEGER, "
                "ldays INTEGER, "
                "lnb INTEGER, "
                "milk REAL, "
                "fat REAL, "
                "protein REAL, "
                "harn REAL, "
                "cells INTEGER, "
                "milkall REAL, "
                "fatall REAL, "
                "proteinall REAL, "
                "farmID nvarchar(10), "
                "messuredate nvarchar(10), "
                "messurenb INTEGER, "
                "PRIMARY KEY(lifenb,farmId),"
                "FOREIGN KEY(farmID) REFERENCES farms(id)"
                ")");
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

bool DataBaseManager::importFromFile(QString fileName)
{
    //StringLength of the eventnumber in the file (positions 3-8 each Line)
    //adding the Length of the first 2 Positions (VN,..)
    int eventNbLen = 8;
    //Len of senseless value properties (1-8), 9+10 =: valLen, 11 = scale
    int senseLessLen = 8;

    //Final array (Cows x Values)
    typedef QList<QString> PropertyList;
    typedef QMap<QString, PropertyList> CowMap;
    CowMap cow;
    //Farm-nb. -> NOT INTEGER (caused by occurable leading zeros)
    QString farmNb;


    //String length of the next read values, length of the scale
    int vLen[20];
    int scale[20];
    //Number of values in the next definition
    int vCount = 0;

    //load file
    QFile MLPData(fileName);
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
    farmNb = farmNb.mid(i,farmNb.length()-i).replace(" ","");

    /////////////////////////////////////
    //     Getting Cow Properties      //
    /////////////////////////////////////

    while (line.at(0) != 'Z')
    {
        //skip to the next definition
        while((line.at(0) != 'D')||(line.at(1) != 'N'))
            line = stream.readLine();

        vCount = 0;
        //read definition
        i = eventNbLen+senseLessLen;
        while(i<line.length())
        {
            vLen[vCount] = (line.mid(i,2)).toInt();
            scale[vCount] = (line.mid(i+2,1)).toInt();
            vCount++;
            i += senseLessLen+3;
        }

        //skip to the next line of values
        while((line.at(0) != 'V')||(line.at(1) != 'N'))
            line = stream.readLine();

        while((line.at(0) == 'V')&&(line.at(1) == 'N'))
        {
            i = eventNbLen + vLen[0];
            //read values
            for(int k=1;k<vCount;k++)
            {
                if (scale[k] != 0)
                {
                    QString num = line.mid(i,vLen[k]).replace(" ","");
                    if (num != "")
                        cow[line.mid(eventNbLen,vLen[0])].push_back(
                            QString::number((num).toFloat()/pow((float)10,scale[k])
                            )
                        );
                    else
                        cow[line.mid(eventNbLen,vLen[0])].push_back(QString("0"));
                }
                else
                {
                    QString num = line.mid(i,vLen[k]).replace(" ","");
                    if (num != "")
                        cow[line.mid(eventNbLen,vLen[0])].push_back(line.mid(i,vLen[k]).replace(" ",""));
                    else
                        cow[line.mid(eventNbLen,vLen[0])].push_back(QString("0"));
                }
                i += vLen[k];
            }
            //next line
            line = stream.readLine();
        }
    }
    MLPData.close();

    for(CowMap::const_iterator iter = cow.begin(); iter!=cow.end();iter++)
        query->exec("INSERT INTO cows VALUES ("
                    "'"+iter.key()+"',"
                    "'"+iter.value()[6]+"',"
                    ""+iter.value()[5]+","
                    ""+iter.value()[18]+","
                    ""+iter.value()[16]+","
                    ""+iter.value()[9]+","
                    ""+iter.value()[10]+","
                    ""+iter.value()[11]+","
                    ""+iter.value()[13]+","
                    ""+iter.value()[12]+","
                    ""+iter.value()[19]+","
                    ""+iter.value()[20]+","
                    ""+iter.value()[22]+","
                    "'"+farmNb+"',"
                    "'"+iter.value()[7].right(2)+"."+iter.value()[7].mid(4,2)+"."+iter.value()[7].left(4)+"',"
                    ""+iter.value()[8]+""
                    ")");

    query->exec("INSERT INTO farms VALUES ('345514', 'Peters Farm', 'Volkmer', 'Peter', 'Dachstraße 9', '03185', 'Drehnow', '098', '097', '', '10.12.1111', '12.12.12')");
    query->exec("INSERT INTO farms VALUES ('123456', 'Mamas Farm', 'Müller', 'Trauthild', 'Einsamer Weg 42', '12345', 'Cottbus', '112', '1100', 'alte Frau...', '12.13.14', '01.21.2001')");

    return true;
}

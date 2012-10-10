#include "DataBaseManager.h"

DataBaseManager::DataBaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("MLPDatabase.sqlite");
    if(!db.open())
    {
        QMessageBox mb;
        mb.setText("Databasekann nicht geöffnet werden.");
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

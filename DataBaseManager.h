#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QVector>

#include <QMessageBox>



class DataBaseManager
{
private:
    QSqlDatabase            db;
    QSqlQuery*              query;

protected:
    void             initializeFirst();

public:
    DataBaseManager();                                          //constructor
    DataBaseManager(const DataBaseManager& dataBaseManager);    //copy constructor
    ~DataBaseManager();                                         //destructor

    QSqlDatabase    getSQLDatabase();
    //returns the opened Database

    void            executeQuery(const QString& aQuery);
    //executes a given statement concerning the database

    void            createTable(const QString& tableName, QVector<QString> attributes);
    //creates a new table in the opened Database using attribut format of SQLITE

    bool            importFromFile(QString filename);
    //reads the given file, parses its information and store them in the database.
    //Returns true if successful
};

#endif // DATABASEMANAGER_H

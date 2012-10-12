#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QVector>

#include <QMessageBox>



class DataBaseManager
{
private:
    QSqlDatabase    db;
    QSqlQuery*      query;

protected:
    void             initializeFirst();

public:
    DataBaseManager();
    DataBaseManager(const DataBaseManager& dataBaseManager);
    ~DataBaseManager();

    QSqlDatabase    getSQLDatabase();
    void            executeQuery(const QString& aQuery);
    void            createTable(const QString& tableName, QVector<QString> attributes);
    bool         importFromFile(QString fileName);
};

#endif // DATABASEMANAGER_H

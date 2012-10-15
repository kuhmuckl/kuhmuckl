#ifndef SESSION_H
#define SESSION_H


#include <QVector>
#include <QGraphicsScene>

#include "Farm.h"
#include "Report.h"
#include "Diagram.h"
#include "Animal.h"
#include "Cow.h"
#include "DataBaseManager.h"

/**Session class
    Contains and manages all functions used by the User Interface.
    It will organize all data in vector (?) - structures, so we
    only have to read them once out of their files.
    Also it is possible to restore last Session at program start.
*/
class Session
{
private:
    QVector<Animal*> animals;
    QVector<Farm*>   farms;
    unsigned int     activeAnimal;      //Only index is stored
    unsigned int     activeFarm;        //Only index is stored

    Diagram*         diagram;           //Maybe a QSet of?
    Report*          report;            //Maybe a QSet of?

    DataBaseManager* dataBaseManager;

public:
    Session();                          //constructor
    Session(const Session& session);    //copy constructor
    ~Session();                         //destructor

    QSqlDatabase    getSQLDatabase();
    Diagram*        getDiagram();
    Report*         getReport();

    Animal*         getAnimal(unsigned int index);
    Animal*         getActiveAnimal();
    Farm*           getFarm(unsigned int index);
    Farm*           getActiveFarm();

    QMap<QString, QString>  colTrans;                       //Name of the col to the shown name
    QList<QString>          tableCon;                       //table configurations
    QList<QString>          cols;
    QList<QString>          filter;
    QString                 order;
    QString                 farmID;

    bool            readNewDataFromFile(QString fileName);  //returns true on success
    void            createDiagram(QString xAxisPropertyName, QString yAxisPropertyName, QGraphicsScene* scene);
    void            setActiveAnimal(unsigned int index);
    void            setActiveFarm(unsigned int index);
};

#endif // SESSION_H

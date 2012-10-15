#include "Session.h"

#include <iostream>

Session::Session()
{
    diagram = new Diagram();
    report = new Report();
    dataBaseManager = new DataBaseManager();
}

Session::Session(const Session &session)
{
    //ToDo: Clear for type
    //animals.clear();
    //animals.reserve(session.animals.size());
    //foreach(Animal* animal, session.animals)
    //    animals.push_back(new Animal(*animal));

    farms.clear();
    farms.reserve(session.farms.size());
    foreach(Farm* farm, session.farms)
        farms.push_back(new Farm(*farm));


    this->diagram = new Diagram(*session.diagram);
    this->report  = new Report(*session.report);
}

Session::~Session()
{
    for(int i = 0; i < animals.size(); i++)
        if(animals[i])
            delete animals[i];
    animals.clear();
    for(int i = 0; i < farms.size(); i++)
        if(farms[i])
            delete farms[i];
    farms.clear();

    delete report;
    delete diagram;
    delete dataBaseManager;

}

QSqlDatabase Session::getSQLDatabase()
{
    return dataBaseManager->getSQLDatabase();
}

Diagram* Session::getDiagram()
{
    return this->diagram;
}

Report* Session::getReport()
{
    return this->report;
}

Animal* Session::getAnimal(unsigned int index)
{
    return this->animals.at(index);
}

Animal* Session::getActiveAnimal()
{
    return this->animals[activeAnimal];
}

Farm* Session::getFarm(unsigned int index)
{
    return this->farms.at(index);
}

Farm* Session::getActiveFarm()
{
    return farms[this->activeFarm];
}

void Session::setActiveAnimal(unsigned int index)
{
    this->activeAnimal = index;
}

void Session::setActiveFarm(unsigned int index)
{
    this->activeFarm = index;
}

bool Session::readNewDataFromFile(QString fileName)
{
    bool success = false;
    //ParseInputs and alter Database

    success = dataBaseManager->importFromFile(fileName);

    return success;
}

void Session::createDiagram(QString xAxisPropertyName, QString yAxisPropertyName){
    QSqlQuery query(getSQLDatabase());
    query.exec("SELECT "+xAxisPropertyName+
               ", "+yAxisPropertyName+" FROM cows "+
               "JOIN farms ON  cows.farmID=farms.ID "+
               "WHERE (cows.farmID="+farmID+")");
    QMessageBox mb;
    if(query.isSelect())
        mb.setText(query.value(1).toString());
    else
        mb.setText("SELECT nicht ausgeführt!");
    mb.exec();
}

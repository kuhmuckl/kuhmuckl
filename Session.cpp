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
    // TODO: Update for Pointer
    this->animals = session.animals;
    this->farms   = session.farms;
    this->diagram = session.diagram;
    this->report  = session.report;
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

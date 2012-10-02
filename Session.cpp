#include "Session.h"

Session::Session()
{

}

Session::Session(const Session &session)
{
    this->animals = session.animals;
    this->farms   = session.farms;
    this->diagram = session.diagram;
    this->report  = session.report;
}

Session::~Session()
{
    animals.clear();
    farms.clear();
}

Diagram Session::getDiagram()
{
    return this->diagram;
}

Report Session::getReport()
{
    return this->report;
}

Animal Session::getAnimal(unsigned int index)
{
    return this->animals.at(index);
}

Farm Session::getFarm(unsigned int index)
{
    return this->farms.at(index);
}

#ifndef ENTITY_H
#define ENTITY_H

#include "Printable.h"

#include "QMap"
#include "QVariant"
#include "QString"
#include "QList"

class Entity : public Printable //abstract class! don't try to instanciate
{
    QMap<QString, QVariant>    properties;
public:
    Entity();                                       //constructor
    Entity(const Entity& entity);                   //copy constructor
    ~Entity();                                      //destructor

    void addProperty(QPair<QString, QVariant> property);
    bool deleteProperty(QString name);              //returns true if successful

    QList<QString> getAllPropertyNames();
    QVariant getValue(QString propertyName);

    virtual bool saveLayoutToFile(QString fileName);        //saves Property names to file and returns true in case of success
    virtual bool loadLayoutFromFile(QString fileName);      //recovers Map from last use from file

    virtual void print() = 0;                       //Every Entity shall be printable
};

#endif // ENTITY_H

#ifndef ENTITY_H
#define ENTITY_H

#include "QMap"
#include "QVariant"
#include "QString"
#include "QList"

class Entity
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

    bool saveLayoutToFile(QString fileName);        //saves Property names to file and returns true in case of success
    bool loadLayoutFromFile(QString fileName);      //recovers Map from last use from file
};

#endif // ENTITY_H

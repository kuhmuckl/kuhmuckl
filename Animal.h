#ifndef ANIMAL_H
#define ANIMAL_H

#include "QVector"
#include "QVariant"
#include "QString"
/**
  This class contains all properties and functions that
  are useful for future animals -besides cows.
  It only describes one animal, not the set of animals.
  */
class Animal
{
    // Do we need a storage over time?
    QVector<QString>    propertyName;
    QVector<QVariant>   propertyValue;
public:
    Animal();                           //constructor
    ~Animal();                          //destructor
    void addProperty(QString name, QVariant value = 0);
    bool deletePropertyByName(QString name);         //returns true if successful
};

#endif // ANIMAL_H

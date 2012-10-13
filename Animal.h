#ifndef ANIMAL_H
#define ANIMAL_H

#include "Entity.h"

/**
  This abstract class contains all properties and functions that
  are useful for future animals -besides cows.
  It only describes one animal, not the set of animals.
  */
class Animal : public Entity //abstract class! don't try to instaciate
{
public:
    Animal();                                       //constructor
    ~Animal();                                      //destructor

    bool exportAsTextFile(QString fileName);
    bool exportAsPDF(QString fileName);

    virtual void print() = 0;                       //pure virtual function makes a class abstract
};

#endif // ANIMAL_H

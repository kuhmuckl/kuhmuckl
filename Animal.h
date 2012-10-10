#ifndef ANIMAL_H
#define ANIMAL_H

#include "Entity.h"

/**
  This class contains all properties and functions that
  are useful for future animals -besides cows.
  It only describes one animal, not the set of animals.
  */
class Animal : Entity
{
public:
    Animal();                                       //constructor
    ~Animal();                                      //destructor

    bool exportAsTextFile(QString fileName);
    bool exportAsPDF(QString fileName);
};

#endif // ANIMAL_H

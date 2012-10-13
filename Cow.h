#ifndef COW_H
#define COW_H

#include "Animal.h"

/**
  First animal derivate. Contains the important functions for
  displaying important information espacially about cows and
  drawing their diagrams.
  Specifies cow-diagram-layouts.
  */
class Cow : public Animal
{
private:
    //
public:
    Cow();  //constructor
    ~Cow(); //destructor

    virtual void print();
};

#endif // COW_H

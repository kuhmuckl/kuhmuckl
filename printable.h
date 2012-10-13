#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <QString>

/**
  Abstract Base class for every Object that shall support
  being printed and stroing layouts.
*/

class Printable
{
public:
    Printable();
    ~Printable();


    virtual bool saveLayoutToFile(QString fileName) = 0;        //saves Property names to file and returns true in case of success
    virtual bool loadLayoutFromFile(QString fileName) = 0;      //recovers Map from last use from file

    virtual void print() = 0;                                   //Every document shall be printable
};

#endif // PRINTABLE_H

#ifndef REPORT_H
#define REPORT_H

#include "Entity.h"

/**
  This class manages the dynamic creation and storage of reports as well
  as the possibility to save a report's layout.
  Maybe we can outsource the layout as another class?
  */
class Report : Entity
{
public:
    Report();       //constructor
    ~Report();      //destructor


    bool exportAsTextFile(QString fileName);
    bool exportAsPDF(QString fileName);
};

#endif // REPORT_H

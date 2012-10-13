#ifndef REPORT_H
#define REPORT_H

#include "Entity.h"

/**
  This class manages the dynamic creation and storage of reports as well
  as the possibility to save a report's layout.
  Maybe we can outsource the layout as another class?
  */
class Report : public Entity
{
public:
    Report();       //constructor
    ~Report();      //destructor

    // The following functions try to convert and save the diagram as
    // a different data type and store them beneath the given file name.
    // Return true on success.
    bool exportAsTextFile(QString fileName);
    bool exportAsPDF(QString fileName);
    bool exportAsDOC(QString fileName);

    virtual void print();
};

#endif // REPORT_H

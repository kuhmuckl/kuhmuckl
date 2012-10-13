#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "Printable.h"

#include <QMap>
#include <QString>

/**
  Diagram class to save and load diagram layouts
  and exporting them.
  */

class Diagram : public Printable
{
private:
    float                           xAxisStep;
    float                           yAxisStep;
    QMap<float, float>              values;
public:
    Diagram();//constructor
    ~Diagram();//destructor

    void            setXAxisStep(float xAxisStep);
    void            setYAxisStep(float yAxisStep);


    float           getYValues(float xValue);
    float           getXAxisStep();
    float           getYAxisStep();

    void            addValue(float xValue, float yValue);
    void            calculateAxisSteps();

    // The following functions try to convert and save the diagram as
    // a different data type and store them beneath the given file name.
    // Return true on success.
    bool            exportAsSVG(QString fileName);
    bool            exportAsJPG(QString fileName);
    bool            exportAsBMP(QString fileName);
    bool            exportAsPDF(QString fileName);

    virtual bool    saveLayoutToFile(QString fileName);        //saves Property names to file and returns true in case of success
    virtual bool    loadLayoutFromFile(QString fileName);      //recovers Map from last use from file

    virtual void    print();
};

#endif // DIAGRAM_H
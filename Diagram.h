#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QVector>
#include <QPair>

/**
  Diagram class to save and load diagram layouts
  and displaying them.
  */

class Diagram
{
private:
    float                           xAxisStep;
    float                           yAxisStep;
    QVector< QPair<float, float> >  values;
public:
    Diagram();//constructor
    ~Diagram();//destructor

    void            setXAxisStep(float xAxisStep);
    void            setYAxisStep(float yAxisStep);

    QVector<float>  getYValues(float xValue);
    QVector<float>  getXValues(float yValue);
    float           getXAxisStep();
    float           getYAxisStep();

    void            addValue(float xValue, float yValue);
    void            calculateAxisSteps();
    bool            exportAsSVG(QString fileName);
    bool            exportAsJPG(QString fileName);
    bool            exportAsBMP(QString fileName);
    bool            exportAsPDF(QString fileName);
};

#endif // DIAGRAM_H

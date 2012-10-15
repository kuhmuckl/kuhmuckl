#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "Printable.h"

#include <QMap>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>

/**
  Diagram class to save and load diagram layouts
  and exporting them.
  */

class Diagram : public Printable
{
private:
    static const int STEP = 30;
    QString                         xAxisName;
    QString                         yAxisName;
    float                           xAxisStep;
    float                           yAxisStep;
    float                           minX;
    float                           minY;
    QMap<float, float>              values;
    QGraphicsScene*                 scene;
    QPixmap*                         pixmap;
protected:
    void drawCaption(QPainter& p, QString title);
    void drawXAxis(QPainter& p);
    void drawYAxis(QPainter& p);
    void drawValues(QPainter& p);
    void drawHorizontalLines(QPainter& p);
    void calculateAxisSteps();
public:
    Diagram();//constructor
    ~Diagram();//destructor

    void            setXAxisName(QString propertyName);
    void            setYAxisName(QString propertyName);
    void            setScene(QGraphicsScene* scene);


    float           getYValues(float xValue);
    QString         getXAxis();
    QString         getYAxis();

    void                    addValue(float xValue, float yValue);
     QGraphicsPixmapItem*   draw(QString title);

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

#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "Printable.h"

#include <QList>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>

/**
  Diagram class to save and load diagram layouts
  and exporting them.
  */

class Diagram : public Printable
{
private:
    static const int STEP = 70;
    static const int DISTANCE = 15;
    static const int CROSS_LENGTH = 3;
    QString                         xAxisName;
    QString                         yAxisName;
    float                           xAxisStep;
    float                           yAxisStep;
    float                           minX;
    float                           minY;
    typedef QPair<float,float> ValuePair;
    QList<ValuePair>                values;
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

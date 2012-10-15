#include "Diagram.h"

Diagram::Diagram():
    xAxisName("x"),
    yAxisName("y"),
    xAxisStep(0),
    yAxisStep(0),
    scene(0),
    pixmap(0)
{
    values.clear();
}

Diagram::~Diagram()
{
    values.clear();
}

QString Diagram::getXAxis(){
    return xAxisName;
}

QString Diagram::getYAxis(){
    return yAxisName;
}

void Diagram::setXAxisName(QString propertyName){
    this->xAxisName = propertyName;
}

void Diagram::setYAxisName(QString propertyName){
    this->yAxisName = propertyName;
}

void Diagram::addValue(float xValue, float yValue){
    values[xValue] = yValue;
}

float Diagram::getYValues(float xValue){
    return values[xValue];
}

void Diagram::calculateAxisSteps()
{
    const int INITIAL_MAXIMUM = 2000000;
    xAxisStep = yAxisStep = 0;
    float maxX, maxY;
    minX=minY=INITIAL_MAXIMUM;
    maxX=maxY=0;
    QMap<float, float>::const_iterator it = values.begin();
    while(it != values.end()){
        it++;
        minX=minX>it.key()?it.key():minX;
        maxX=maxX<it.key()?it.key():maxX;
        minY=minY>it.value()?it.value():minY;
        maxY=maxY<it.value()?it.value():maxY;
    }
    xAxisStep =(maxX-minX)/qRound(pixmap->width()/STEP)-1;
    yAxisStep =(maxY-minY)/qRound(pixmap->height()/STEP)-1;
}

void Diagram::setScene(QGraphicsScene *scene){
    this->scene=scene;
    this->pixmap = new QPixmap(scene->width(),scene->height());
}

void Diagram::drawCaption(QPainter& p, QString title){
    p.drawText(0,0,pixmap->width(),30,
               Qt::TextWordWrap|Qt::AlignCenter,
               title);
}

void Diagram::drawXAxis(QPainter& p){
    const int DISTANCE = 15;
    p.setPen(QPen(QBrush(Qt::black),3));
    p.drawLine(DISTANCE,                    pixmap->height()-2*DISTANCE,
               pixmap->width()-1.5*DISTANCE,pixmap->height()-2*DISTANCE);
    p.drawLine(pixmap->width()-    DISTANCE,pixmap->height()-2*DISTANCE,
               pixmap->width()-2*  DISTANCE,pixmap->height()-2*DISTANCE-2);
    p.drawLine(pixmap->width()-    DISTANCE,pixmap->height()-2*DISTANCE,
               pixmap->width()-2*  DISTANCE,pixmap->height()-2*DISTANCE+2);

}

void Diagram::drawYAxis(QPainter& p){
    const int DISTANCE = 15;
    p.setPen(QPen(QBrush(Qt::black),3));
    p.drawLine(2*DISTANCE, pixmap->height()-DISTANCE,
               2*DISTANCE, 1.5*DISTANCE);
    p.drawLine(2*DISTANCE, DISTANCE,
               2*DISTANCE-2, 2*DISTANCE);
    p.drawLine(2*DISTANCE, DISTANCE,
               2*DISTANCE+2, 2*DISTANCE);
}

void Diagram::drawValues(QPainter& p){
    calculateAxisSteps();
}

void Diagram::drawHorizontalLines(QPainter& p){

}

QGraphicsPixmapItem* Diagram::draw(QString title){
    if(pixmap == 0)
        return 0;
    QPainter p(pixmap);
    p.setPen(QPen(Qt::white));
    p.setBrush(Qt::white);
    p.drawRect(pixmap->rect());

    drawCaption(p, title);
    drawXAxis(p);
    drawYAxis(p);
    drawValues(p);
    drawHorizontalLines(p);

    return new QGraphicsPixmapItem(*pixmap,0,scene);
}

bool Diagram::exportAsSVG(QString fileName)
{
    bool success = false;
    //Convert Data to SVG
    //Store SVG to Filename
    return success;
}

bool Diagram::exportAsBMP(QString fileName)
{
    return pixmap->save(fileName, "BMP");
}

bool Diagram::exportAsJPG(QString fileName)
{
    return pixmap->save(fileName, "JPG");
}

bool Diagram::exportAsPDF(QString fileName)
{
    bool success = false;
    //Convert Data to PDF
    //Store SVG to Filename
    return success;
}

bool Diagram::saveLayoutToFile(QString fileName)
{
    bool success = false;
    //Save Axis to Filename
    return success;
}

bool Diagram::loadLayoutFromFile(QString fileName)
{
    bool success = false;
    //load last Axis configuration
    //maybe source?
    return success;
}

void Diagram::print()
{

}

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
    values.push_back(ValuePair(xValue,yValue));
}

void Diagram::calculateAxisSteps()
{
    const int INITIAL_MAXIMUM = 2000000;
    xAxisStep = yAxisStep = 0;
    float maxX, maxY;
    minX=minY=INITIAL_MAXIMUM;
    maxX=maxY=0;
    QList<ValuePair>::const_iterator it = values.begin();
    while(it != values.end()){
        it++;
        minX=minX>(*it).first?(*it).first:minX;
        maxX=maxX<(*it).first?(*it).first:maxX;
        minY=minY>(*it).second?(*it).second:minY;
        maxY=maxY<(*it).second?(*it).second:maxY;
    }
    xAxisStep =(maxX-minX)/qRound((pixmap->width()-4*DISTANCE)/STEP);
    yAxisStep =(maxY-minY)/qRound((pixmap->height()-4*DISTANCE)/STEP);
}

void Diagram::setScene(QGraphicsScene *scene){
    this->scene=scene;
    this->pixmap = new QPixmap(scene->width(),scene->height());
}

void Diagram::drawCaption(QPainter& p, QString title){
    p.setPen(QPen(Qt::black));
    p.drawText(0,0,pixmap->width(),30,
               Qt::TextWordWrap|Qt::AlignCenter,
               title);
}

void Diagram::drawXAxis(QPainter& p){
    p.setPen(QPen(QBrush(Qt::black),3));
    p.drawLine(DISTANCE,                    pixmap->height()-2*DISTANCE,
               pixmap->width()-1.5*DISTANCE,pixmap->height()-2*DISTANCE);
    p.drawLine(pixmap->width()-    DISTANCE,pixmap->height()-2*DISTANCE,
               pixmap->width()-2*  DISTANCE,pixmap->height()-2*DISTANCE-2);
    p.drawLine(pixmap->width()-    DISTANCE,pixmap->height()-2*DISTANCE,
               pixmap->width()-2*  DISTANCE,pixmap->height()-2*DISTANCE+2);
    for(int i = 1; i<(pixmap->width()-1.5*DISTANCE)/STEP-1;i++)
    {
        p.setPen(QPen(QBrush(Qt::black),3));
        p.drawLine(STEP*i+2*DISTANCE,pixmap->height()-1.5*DISTANCE,
                   STEP*i+2*DISTANCE,pixmap->height()-2*DISTANCE);
        p.setPen(QPen(Qt::black));
        p.drawText(STEP*(i-0.1)+2*DISTANCE,pixmap->height()-1.4*DISTANCE,
                   STEP*(i+0.3)+2*DISTANCE,pixmap->height()-DISTANCE,
                   Qt::TextWordWrap|Qt::AlignTop|Qt::AlignLeft,
                   QString::number(minX+i*xAxisStep,'g',4));
    }
}

void Diagram::drawYAxis(QPainter& p){
    p.setPen(QPen(QBrush(Qt::black),3));
    p.drawLine(2*DISTANCE, pixmap->height()-DISTANCE,
               2*DISTANCE, 1.5*DISTANCE);
    p.drawLine(2*DISTANCE, DISTANCE,
               2*DISTANCE-2, 2*DISTANCE);
    p.drawLine(2*DISTANCE, DISTANCE,
               2*DISTANCE+2, 2*DISTANCE);
    for(int i = 1; i<(pixmap->width()-1.5*DISTANCE)/STEP-1;i++)
    {
        p.setPen(QPen(QBrush(Qt::black),3));
        p.drawLine(2  *DISTANCE,pixmap->height()-2*DISTANCE-i*STEP,
                   1.5*DISTANCE,pixmap->height()-2*DISTANCE-i*STEP);
        p.setPen(QPen(Qt::black));
        p.drawText(0,           pixmap->height()-2*DISTANCE-(i)*STEP,
                   1.4*DISTANCE,pixmap->height()-2*DISTANCE-(i-0.3)*STEP,
                   Qt::AlignTop|Qt::AlignLeft,
                   QString::number(minY+i*yAxisStep,'g',4));
    }
}

void Diagram::drawValues(QPainter& p){
    p.setPen(QPen(QBrush(Qt::black),3));
    QList<ValuePair>::const_iterator it = values.begin();
    while(it != values.end()){
        it++;
        int x = (*it).first;
        int y = (*it).second;
        y = pixmap->height()-2*DISTANCE;
        x = x/xAxisStep*STEP;
        y -= y/yAxisStep*STEP;
        x += 2*DISTANCE;
        p.drawLine(x-CROSS_LENGTH, y-CROSS_LENGTH,
                   x+CROSS_LENGTH, y+CROSS_LENGTH);
        p.drawLine(x-CROSS_LENGTH, y+CROSS_LENGTH,
                   x+CROSS_LENGTH, y-CROSS_LENGTH);
    }
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

    calculateAxisSteps();

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

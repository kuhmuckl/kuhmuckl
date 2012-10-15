#include "Diagram.h"

Diagram::Diagram():
    xAxisName("x"),
    yAxisName("y")
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
    xAxisName = yAxisName = 10;
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
    bool success = false;
    //Convert Data to BMP
    //Store SVG to Filename
    return success;
}

bool Diagram::exportAsJPG(QString fileName)
{
    bool success = false;
    //Convert Data to JPG
    //Store SVG to Filename
    return success;
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

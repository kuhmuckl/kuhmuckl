#include "Diagram.h"

Diagram::Diagram():
    xAxisStep(0),
  yAxisStep(0)
{
    values.clear();
}

Diagram::~Diagram()
{
    values.clear();
}

float Diagram::getXAxisStep(){
    return xAxisStep;
}

float Diagram::getYAxisStep(){
    return yAxisStep;
}

void Diagram::setXAxisStep(float xAxisStep){
    this->xAxisStep = xAxisStep;
}

void Diagram::setYAxisStep(float yAxisStep){
    this->yAxisStep = yAxisStep;
}

void Diagram::addValue(float xValue, float yValue){
    values[xValue] = yValue;
}

float Diagram::getYValues(float xValue){
    return values[xValue];
}

void Diagram::calculateAxisSteps()
{
    xAxisStep = yAxisStep = 10;
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

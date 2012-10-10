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
    values.push_back(QPair<float, float>(xValue, yValue));
}

QVector<float> Diagram::getYValues(float xValue){
    QVector<float> result;
    for(int i = 0; i < values.size();i++)
        if(values[i].first == xValue)
            result.push_back(values[i].second);
    return result;
}

QVector<float> Diagram::getXValues(float yValue){
    QVector<float> result;
    for(int i = 0; i < values.size();i++)
        if(values[i].second == yValue)
            result.push_back(values[i].first);
    return result;
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

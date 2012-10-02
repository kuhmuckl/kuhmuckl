#ifndef REPORT_H
#define REPORT_H

#include "QVector"
#include "QVariant"
#include "QString"

/**
  This class manages the dynamic creation and storage of reports as well
  as the possibility to save a report's layout.
  Maybe we can outsource the layout as another class?
  */
class Report
{
private:
    QVector<QString>    propertyName;
    QVector<QVariant>   propertyValue;
public:
    Report();       //constructor
    ~Report();      //destructor
    void addProperty(QString name, QVariant value = 0);
    bool deletePropertyByName(QString name);         //returns true if successful
    void saveLayout(QString fileName);               //saves Property nmaes to file
};

#endif // REPORT_H

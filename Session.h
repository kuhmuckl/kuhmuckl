#ifndef SESSION_H
#define SESSION_H


#include <QVector>

#include "Farm.h"
#include "Report.h"
#include "Diagram.h"
#include "Animal.h"
#include "Cow.h"

/**Session class
    Contains and manages all functions used by the User Interface.
    It will organize all data in vector (?) - structures, so we
    only have to read them once out of their files.
    Also it is possible to restore last Session at program start.
*/
class Session
{
private:
    QVector<Animal> animals;
    QVector<Farm>   farms;
    Diagram         diagram;    //Maybe a QSet of?
    Report          report;     //Maybe a QSet of?
public:
    Session();//constructor
    Session(const Session& session);//copy constructor
    ~Session();//destructor

    Diagram  getDiagram();
    Report   getReport();

    Animal   getAnimal(unsigned int index);
    Farm     getFarm(unsigned int index);
};

#endif // SESSION_H

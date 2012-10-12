#ifndef FARM_H
#define FARM_H

#include "Entity.h"

/** class Farm
  Database representation of farms,
  inherits Enitity and is so printable.
*/

class Farm : public Entity
{
public:
    Farm();//constructor
    ~Farm();//destructor

    virtual void print();
};

#endif // FARM_H

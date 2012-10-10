#ifndef FARM_H
#define FARM_H

#include "Entity.h"

class Farm : public Entity
{
public:
    Farm();//constructor
    ~Farm();//destructor

    virtual void print();
};

#endif // FARM_H

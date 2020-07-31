#include "id.h"

Id::Id()
{
    //ctor
}

Id::~Id()
{
    //dtor
}

Id::Id(const Id& other)
{
    //copy ctor
}

Id& Id::operator=(const Id& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

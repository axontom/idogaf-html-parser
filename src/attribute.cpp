#include "attribute.h"

Attribute::Attribute()
{
    //ctor
}

Attribute::~Attribute()
{
    //dtor
}

Attribute::Attribute(const Attribute& other)
{
    //copy ctor
}

Attribute& Attribute::operator=(const Attribute& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

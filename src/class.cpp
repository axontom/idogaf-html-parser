#include "class.h"

Class::Class()
{
    //ctor
}

Class::~Class()
{
    //dtor
}

Class::Class(const Class& other)
{
    //copy ctor
}

Class& Class::operator=(const Class& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

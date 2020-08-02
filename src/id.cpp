#include "id.h"

namespace idogaf
{
Id::Id() : Attribute()
{
    //ctor
    name_ = "id";
}

Id::~Id()
{
    //dtor
}

Id::Id(const Id& other) : Attribute(other)
{
    //copy ctor
    name_ = "id";
}

Id::Id(const Attribute& attribute)
{
    name_ = "id";
    value_ = attribute.value_;
}

Id& Id::operator=(const Id& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    name_ = "id";
    value_ = rhs.value_;
    return *this;
}
}

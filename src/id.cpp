#include "id.h"

namespace idogaf
{
Id::Id() : Attribute()
{
    //ctor
    name_ = Id.GetStaticName();
}

Id::~Id()
{
    //dtor
}

Id::Id(const Id& other) : Attribute(other)
{
    //copy ctor
    name_ = Id.GetStaticName();
}

Id::Id(const Attribute& attribute)
{
    name_ = Id.GetStaticName();
    value_ = attribute.value_;
}

Id& Id::operator=(const Id& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    name_ = Id.GetStaticName();
    value_ = rhs.value_;
    return *this;
}

static std::string Id::GetStaticName() { return "id"; }
}

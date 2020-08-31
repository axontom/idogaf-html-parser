#include "id.h"

namespace idogaf
{

Id::Id() : Attribute()
{
    name_ = Id::GetStaticName();
}

Id::Id(const Id& other) : Attribute(other)
{
    name_ = Id::GetStaticName();
}

Id::Id(const Attribute& attribute)
{
    name_ = Id::GetStaticName();
    value_ = attribute.GetValue();
}

Id& Id::operator=(const Id& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    name_ = Id::GetStaticName();
    value_ = rhs.value_;
    return *this;
}

//Getters
std::string Id::GetStaticName()
{
    return "id";
}

//Setters
void Id::SetName(std::string name) {}

}

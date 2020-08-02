#include "attribute.h"

namespace idogaf
{
Attribute::Attribute()
{
    //ctor
    name_ = std::string();
    value_ = std::string();
}

Attribute::Attribute(std::string name)
{
    //ctor
    name_ = name;
    value_ = std::string();
}

Attribute::Attribute(std::string name, std::string value)
{
    //ctor
    name_ = name;
    value_ = value;
}

Attribute::~Attribute()
{
    //dtor
}

Attribute::Attribute(const Attribute& other)
{
    //copy ctor
    name_ = other.name_;
    value_ = other.value_;
}

Attribute& Attribute::operator=(const Attribute& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    name_ = rhs.name_;
    value_ = rhs.value_;
    return *this;
}

//Getters
std::string Attribute::GetName() { return name_; }
std::string Attribute::GetValue() { return value_; }

//Setters
void Attribute::SetName(std::string name) { name_ = name; }
void Attribute::SetValue(std::string value) { value_ = value; }
}

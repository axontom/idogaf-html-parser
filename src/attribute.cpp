#include "attribute.h"

namespace idogaf
{

Attribute::Attribute()
{
    name_ = std::string();
    value_ = std::string();
}

Attribute::Attribute(const std::string& name)
{
    name_ = name;
    value_ = std::string();
}

Attribute::Attribute(const std::string& name, const std::string& value)
{
    name_ = name;
    value_ = value;
}

Attribute::Attribute(const Attribute& other)
{
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
std::string Attribute::GetName() const
{
    return name_;
}
std::string Attribute::GetValue() const
{
    return value_;
}

//Setters
void Attribute::SetName(const std::string& name)
{
    name_ = name;
}
void Attribute::SetValue(const std::string& value)
{
    value_ = value;
}

}

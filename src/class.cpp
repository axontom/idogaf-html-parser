#include "class.h"

#include <sstream>

namespace idogaf
{

Class::Class() : Attribute()
{
    name_ = Class::GetStaticName();
    classes_ = std::vector<std::string>();
}

Class::Class(const Attribute& attribute)
{
    name_ = Class::GetStaticName();
    value_ = attribute.GetValue();
    classes_ = std::vector<std::string>();
    if(!value_.empty())
    {
        std::stringstream ss = std::stringstream(value_);
        std::string buffer = std::string();
        while (ss.good())
        {
            ss >> buffer;
            if (buffer.empty()) break;
            classes_.push_back(buffer);
        }
    }
}

Class::Class(const Class& other)
{
    name_ = Class::GetStaticName();
    value_ = other.value_;
    classes_ = other.classes_;
}

Class& Class::operator=(const Class& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    name_ = Class::GetStaticName();
    value_ = rhs.value_;
    classes_ = rhs.classes_;
    return *this;
}

//Getters
std::vector<std::string> Class::GetClassesInVector()
{
    return classes_;
}
std::string Class::GetStaticName()
{
    return "class";
}

//Setters
void Class::SetName(std::string name) {}

//Other
bool Class::Matches(std::string className)
{
    for(auto it = classes_.begin(); it != classes_.end(); ++it)
    {
        if(*it == className) return true;
    }
    return false;
}
}

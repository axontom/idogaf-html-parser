#include <sstream>
#include "class.h"

namespace idogaf
{
Class::Class() : Attribute()
{
    //ctor
    name_ = Class.GetStaticName();
    classes_ = std::vector<std::string>();
}


Class::Class(const Attribute& attribute)
{
    name_ = Class.GetStaticName();
    value_ = attribute.value_;
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
    //copy ctor
    name_ = Class.GetStaticName();
    value_ = other.value_;
    classes_ = other.classes_;
}

Class::~Class()
{
    //dtor
}

Class& Class::operator=(const Class& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
}

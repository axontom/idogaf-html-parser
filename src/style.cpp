#include "style.h"

namespace idogaf
{
Style::Style() : Attribute()
{
    name_ = Style::GetStaticName();
    styles_ = std::vector<DStringPair>();
}

Style::Style(const Style& other)
{
    name_ = Style::GetStaticName();
    value_ = other.value_;
    styles_ = other.styles_;
}

Style::Style(const Attribute& attribute)
{
    name_ = Style::GetStaticName();
    value_ = attribute.GetValue();
    styles_ = std::vector<DStringPair>();
    ParseStringForStyles(attribute.GetValue());

}

Style& Style::operator=(const Style& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    name_ = Style::GetStaticName();
    value_ = rhs.value_;
    styles_ = rhs.styles_;
    return *this;
}

//Getters
std::string Style::GetStaticName()
{
    return "style";
}

//Setters
void Style::SetName(const std::string& name) {}

//Protected member functions
unsigned int Style::ParseStringForStyles(const std::string& str)
{
    std::string s = str;
    unsigned int counter = 0;
    while(true)
    {
        DStringPair buffer;
        size_t colonPos = s.find(':');
        size_t semicolonPos = s.find(';');
        if( colonPos == std::string::npos ||
                semicolonPos == std::string::npos ) break;
        buffer.name = s.substr(0, colonPos);
        buffer.value = s.substr(colonPos+1, semicolonPos-colonPos-1);
        styles_.push_back(buffer);
        value_ += s.substr(0, semicolonPos+1);
        counter++;
        s = s.substr(semicolonPos+1, std::string::npos);
    }
    return counter;
}
}

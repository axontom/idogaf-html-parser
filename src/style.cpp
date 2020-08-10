#include "style.h"

namespace idogaf
{
Style::Style() : Attribute()
{
    //ctor
    name_ = Style.GetStaticName();
    styles_ = std::vector<DStringPair>();
}

Style::Style(const Attribute& attribute)
{
    name_ = Style.GetStaticName();
    value_ = "";
    styles_ = std::vector<DStringPair>();
    ParseStringForStyles(attribute.value_);

}

Style& Style::operator=(const Style& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    name_ = Style.GetStaticName();
    value_ = rhs.value_;
    return *this;
}

Style::~Style()
{
    //dtor
}

//Protected member functions
unsigned int Style::ParseStringForStyles(std::string str)
{
    unsigned int counter = 0;
    while(true)
    {
        DStringPair buffer;
        size_t colonPos = str.find(':');
        size_t semicolonPos = str.find(';');
        if( colonPos == std::string::npos ||
            semicolonPos == std::string::npos ) break;
        buffer.name = str.substr(0, colonPos);
        buffer.value = str.substr(colonPos+1, semicolonPos-colonPos-1);
        styles_.push_back(buffer);
        value_ += str.substr(0, semicolonPos+1);
        counter++;
        str = str.substr(semicolonPos+1, std::string::npos);
    }
    return counter;
}
}

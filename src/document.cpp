#include "document.h"

namespace idogaf
{
Document::Document()
{
    //ctor
}

Document::~Document()
{
    //dtor
}

Document::Document(const Document& other)
{
    //copy ctor
}

Document& Document::operator=(const Document& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
}

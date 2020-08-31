#include "document.h"

namespace idogaf
{

Document::Document()
{
    root_ = Element();
    doctype_ = std::string();
}


Document::Document(const Document& other)
{
    root_ = other.root_;
    doctype_ = other.doctype_;
}

Document& Document::operator=(const Document& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    root_ = rhs.root_;
    doctype_ = rhs.doctype_;
    return *this;
}

//Getters
std::string Document::GetDoctype()
{
    return doctype_;
}
Element Document::GetRoot()
{
    return root_;
}
Element* Document::GetRootPtr()
{
    return &root_;
}
bool Document::Empty()
{
    return doctype_.empty() && root_.Empty();
}

//Setters
void Document::SetDoctype(std::string doctype)
{
    doctype_ = doctype;
}
void Document::SetRoot(Element root)
{
    root_ = root;
}

}

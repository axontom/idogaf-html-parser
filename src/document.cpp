#include "document.h"

namespace idogaf
{
Document::Document()
{
    //ctor
    root_ = nullptr;
    doctype_ = "";
}


Document::Document(const Document& other)
{
    //copy ctor
    root_ = other.root_;
    doctype_ = other.doctype_;
}

Document::~Document()
{
    //dtor
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
std::string Document::GetDoctype() { return doctype_; }
Element* Document::GetRoot() { return root_; }
bool Document::IsEmpty() { return doctype_.empty() && root_ == nullptr; }

//Setters
void Document::SetDoctype(std::string doctype) { doctype_ = doctype; }
void Document::SetRoot(Element* root)
{
    root_ = root;
    if(root != nullptr)
        root_->RemoveParent();
}

}

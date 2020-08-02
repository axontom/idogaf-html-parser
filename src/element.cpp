#include "element.h"

namespace idogaf
{
//Constructors
Element::Element()
{
    //ctor
    SetDefaultValues();
}

Element::Element(std::string name)
{
    SetDefaultValues();
    name_ = name;
}

Element::Element(std::string name, Element* parent)
{
    SetDefaultValues();
    name_ = name;
    parent_ = parent;
}

Element::Element(std::string name, std::string text,
                 std::vector<Element*> children, Element* parent,
                 std::vector<Attribute> attributes)
{
    name_ = name;
    text_ = text;
    children_ = children != nullptr ? children : vector<Element*>();
    parent_ = parent;
    attributes_ = vector<Attribute>();
    if (attributes != nullptr)
    {
        for(int i = 0; i < attributes.size(); i++)
        {
            if(attributes[i].GetName() == "class")
            {
                class_ = Class(attributes[i]);
            }
            else if(attributes[i].GetName() == "id")
            {
                id_ = Id(attributes[i]);
            }
            else if(attributes[i].GetName() == "style")
            {
                style_ = Style(attributes[i]);
            }
            else
            {
                attributes_.push_back(attributes[i]);
            }
        }
    }
}

Element::Element(std::string name, std::string text,
                 std::vector<Element*> children, Element* parent,
                 Class css_class, Id id, Style style)
{
    name_ = name;
    text_ = text;
    children_ = children != nullptr ? children : vector<Element*>();
    parent_ = parent;
    class_ = css_class;
    id_ = id;
    style_ = style;
}

Element::Element(const Element& other)
{
    //copy ctor
    name_ = other.name_;
    text_ = other.text_;
    children_ = other.children_;
    parent_ = other.parent_;
    attributes_ = other.attributes_;
    class_ = other.class_;
    id_ = other.id_;
    style_ = other.style_;
}

Element& Element::operator=(const Element& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    name_ = other.name_;
    text_ = other.text_;
    children_ = other.children_;
    parent_ = other.parent_;
    attributes_ = other.attributes_;
    class_ = other.class_;
    id_ = other.id_;
    style_ = other.style_;
    return *this;
}

//Destructor
Element::~Element()
{
    //dtor
}

//Public member fuctions

//Protected member functions
void Element::SetDefaultValues()
{
    name_       = std::string();
    text_       = std::string();
    children_   = std::vector<Element*>();
    parent_     = nullptr;
    attributes_ = std::vector<Attribute>();
    class_      = nullptr;
    id_         = nullptr;
    style_      = nullptr;
}
}

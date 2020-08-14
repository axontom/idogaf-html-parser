#include "element.h"
#include "manager.h"

namespace idogaf
{
//Constructors
Element::Element()
{
    //ctor
    SetDefaultValues();
    Manager::Add(this);
}

Element::Element(std::string name)
{
    SetDefaultValues();
    name_ = name;
    Manager::Add(this);
}

Element::Element(std::string name, Element* parent)
{
    SetDefaultValues();
    name_ = name;
    SetParent(parent);
    Manager::Add(this);
}

Element::Element(std::string name, std::string text,
                 std::vector<Element*> children, Element* parent,
                 std::vector<Attribute> attributes)
{
    name_ = name;
    text_ = text;
    children_ = children;
    SetParent(parent);
    attributes_ = std::vector<Attribute>();
    for(size_t i = 0; i < attributes.size(); i++)
    {
        if(attributes[i].GetName() == "class")
        {
            *class_ = Class(attributes[i]);
        }
        else if(attributes[i].GetName() == "id")
        {
            *id_ = Id(attributes[i]);
        }
        else if(attributes[i].GetName() == "style")
        {
            *style_ = Style(attributes[i]);
        }
        else
        {
            attributes_.push_back(attributes[i]);
        }
    }
    Manager::Add(this);
}

Element::Element(std::string name, std::string text,
                 std::vector<Element*> children, Element* parent,
                 Class css_class, Id id, Style style)
{
    name_ = name;
    text_ = text;
    children_ = children;
    SetParent(parent);
    *class_ = css_class;
    *id_ = id;
    *style_ = style;
    Manager::Add(this);
}
/*  Removed 14.08.20
    Only poiters should be copied, not objects.
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
    Manager::Add(this);
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
*/

void Element::operator delete(Element* element, std::destroying_delete_t)
{
    element->~Element();
    delete(element);
}

//Public member fuctions

//Getters
std::string Element::GetName() { return name_; }
std::string Element::GetText() { return text_; }
Element* Element::GetParent() { return parent_; }
Class* Element::GetClass() { return class_; }
Id* Element::GetId() { return id_; }
Style* Element::GetStyle() { return style_; }
std::vector<Element*> Element::GetChildren() { return children_; }
std::vector<Element*> Element::GetChildrenByTagName(std::string name)
{
    std::vector<Element*> result = std::vector<Element*>();
    for(auto it = children_.begin();it != children_.end();++it)
    {
        if((*it)->GetName() == name)
            result.push_back(*it);
    }
    return result;
}
std::vector<Element*> Element::GetChildrenByClassName(std::string name)
{
    std::vector<Element*> result = std::vector<Element*>();
    for(auto it = children_.begin();it != children_.end();++it)
    {
        if((*it)->GetClass()->Matches(name))
            result.push_back(*it);
    }
    return result;
}
std::vector<Element*> Element::GetChildrenById(std::string id)
{
    std::vector<Element*> result = std::vector<Element*>();
    for(auto it = children_.begin();it != children_.end();++it)
    {
        if((*it)->GetId()->GetValue() == id)
            result.push_back(*it);
    }
    return result;
}
Element* Element::GetFirstChild()
{
    return children_.size() > 0 ? children_[0] : nullptr;
}
Element* Element::GetChildAt(unsigned int position)
{
    return children_.size() > position ? children_[position] : nullptr;
}
Element* Element::GetLastChild()
{
    return children_.size() > 0 ? children_.back() : nullptr;
}
unsigned int Element::GetChildrenCount() { return children_.size(); }
std::vector<Attribute> Element::GetAttributes()
{
    if(style_ != nullptr) attributes_.insert(attributes_.begin(), *style_);
    if(class_ != nullptr) attributes_.insert(attributes_.begin(), *class_);
    if(id_ != nullptr) attributes_.insert(attributes_.begin(), *id_);

    return attributes_;
}
Attribute* Element::GetAttributeByName(std::string name)
{
    if(name == Class::GetStaticName()) return class_;
    if(name == Id::GetStaticName()) return id_;
    if(name == Style::GetStaticName()) return style_;

    for(auto it = attributes_.begin();it != attributes_.end();++it)
    {
        if(it->GetName() == name) return &(*it);
    }
    return nullptr;
}

//Setters
void Element::SetName(std::string name) { name_ = name; }
void Element::SetText(std::string text) { text_ = text; }
void Element::AddText(std::string text) { text_ += text; }
void Element::SetParent(Element* parent)
{
    //Remove this element from it's current parent vector.
    if(parent_ != nullptr)
    {
        for(auto it = parent_->children_.begin();
            it != parent_->children_.end();++it)
        {
            if(*it == this)
                parent_->children_.erase(it);
        }
    }
    parent_ = parent;
    if(parent_ == nullptr) return;
    //Add this to the new parents vector if it's not already there.
    for(auto it = parent_->children_.begin();
        it != parent_->children_.end();++it)
    {
        if(*it == this) return;
    }
    parent_->children_.push_back(this);
}
void Element::RemoveParent()
{
    if(parent_ != nullptr)
    {
        for(auto it = parent_->children_.begin();
            it != parent_->children_.end();++it)
        {
            if(*it == this)
                parent_->children_.erase(it);
        }
    }
    parent_ = nullptr;
}
void Element::SetClass(Class newClass) { *class_ = newClass; }
void Element::SetId(Id id) { *id_ = id; }
void Element::SetStyle(Style style) { *style_ = style; }

void Element::RemoveChildren()
{
    for(auto it = children_.begin();it != children_.end();++it)
        (*it)->parent_ = nullptr;
    children_.clear();
}
void Element::RemoveChildAt(unsigned int position)
{
    if(position >= children_.size()) return;

    children_[position]->parent_ = nullptr;
    children_.erase(children_.begin()+position);
}
void Element::AddChild(Element* child)
{
    if(child == nullptr) return;

    for(auto it = children_.begin();it != children_.end();++it)
    {
        if(*it == child) return;
    }

    child->RemoveParent();
    children_.push_back(child);
    child->parent_ = this;
}
void Element::AddChildAt(Element* child, unsigned int position)
{
    if(position >= children_.size()) return;
    if(child == nullptr) return;

    for(auto it = children_.begin();it != children_.end();++it)
    {
        if(*it == child) return;
    }

    child->RemoveParent();
    children_.insert(children_.begin()+position, child);
    child->parent_ = this;
}
void Element::AddChildren(std::vector<Element*> children)
{
    for(auto it = children.begin();it != children.end();++it)
        (*it)->RemoveParent();
    children_.insert(children_.end(), children.begin(), children.end());
}

void Element::RemoveAttributes()
{
    attributes_.clear();
    class_ = nullptr;
    id_ = nullptr;
    style_ = nullptr;
}
void Element::RemoveAttributeByName(std::string name)
{
    if(name == Class::GetStaticName())
    {
        class_ = nullptr;
        return;
    }
    if(name == Id::GetStaticName())
    {
        id_ = nullptr;
        return;
    }
    if(name == Style::GetStaticName())
    {
        style_ = nullptr;
        return;
    }

    for(auto it = attributes_.begin();it != attributes_.end();++it)
    {
        if(it->GetName() == name)
        {
            attributes_.erase(it);
            return;
        }
    }
}
void Element::AddAtrribute(Attribute attribute)
{
    if(attribute.GetName() == Class::GetStaticName())
    {
        *class_ = Class(attribute);
        return;
    }
    if(attribute.GetName() == Id::GetStaticName())
    {
        *id_ = Id(attribute);
        return;
    }
    if(attribute.GetName() == Style::GetStaticName())
    {
        *style_ = Style(attribute);
        return;
    }

    for(auto it = attributes_.begin();it != attributes_.end();++it)
    {
        if(it->GetName() == attribute.GetName())
        {
            *it = attribute;
            return;
        }
    }

    attributes_.push_back(attribute);
}


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

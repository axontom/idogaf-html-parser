#include "element.h"
#include "search.h"

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

Element::Element(std::string name, std::string text,
    std::vector<Element> children, std::vector<Attribute> attributes)
{
    name_ = name;
    text_ = text;
    children_ = children;
    for(auto it = children_.begin();it != children_.end();++it)
        it->parent_ = this;
    attributes_ = std::vector<Attribute>();
    for(size_t i = 0; i < attributes.size(); i++)
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
    parent_ = nullptr;
}

Element::Element(std::string name, std::string text,
                 std::vector<Element> children, Class css_class, Id id, Style style)
{
    name_ = name;
    text_ = text;
    children_ = children;
    for(auto it = children_.begin();it != children_.end();++it)
        it->parent_ = this;
    class_ = css_class;
    id_ = id;
    style_ = style;
    parent_ = nullptr;
}

Element::Element(const Element& other)
{
    //copy ctor
    name_ = other.name_;
    text_ = other.text_;
    children_ = other.children_;
    for(auto it = children_.begin();it != children_.end();++it)
        it->parent_ = this;
    parent_ = nullptr;
    attributes_ = other.attributes_;
    class_ = other.class_;
    id_ = other.id_;
    style_ = other.style_;
}

Element& Element::operator=(const Element& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    name_ = rhs.name_;
    text_ = rhs.text_;
    children_ = rhs.children_;
    for(auto it = children_.begin();it != children_.end();++it)
        it->parent_ = this;
    parent_ = nullptr;
    attributes_ = rhs.attributes_;
    class_ = rhs.class_;
    id_ = rhs.id_;
    style_ = rhs.style_;
    return *this;
}

//Public member fuctions

//Getters
Element Element::Copy() { return Element(*this); }
bool Element::Empty()
{
    return name_.empty() && text_.empty() && attributes_.empty()
        && children_.empty() && class_.GetValue().empty()
        && id_.GetValue().empty() && style_.GetValue().empty();
}
std::string Element::GetName() { return name_; }
std::string Element::GetText() { return text_; }
Element* Element::GetParent() { return parent_; }
Class Element::GetClass() { return class_; }
Id Element::GetId() { return id_; }
Style Element::GetStyle() { return style_; }
std::vector<Element> Element::GetChildren() { return children_; }
std::vector<Element*> Element::GetChildrenPtr()
{
    std::vector<Element*> pointers;
    for(auto it = children_.begin();it != children_.end();++it)
        pointers.push_back(&(*it));
    return pointers;
}
std::vector<Element> Element::GetChildrenByTagName(std::string name)
{
    std::vector<Element> result;
    for(auto it = children_.begin();it != children_.end();++it)
    {
        if(it->GetName() == name)
            result.push_back(*it);
    }
    return result;
}
std::vector<Element*> Element::GetChildrenPtrByTagName(std::string name)
{
    std::vector<Element*> result;
    for(auto it = children_.begin();it != children_.end();++it)
    {
        if(it->GetName() == name)
            result.push_back(&(*it));
    }
    return result;
}
std::vector<Element> Element::GetChildrenByClassName(std::string name)
{
    std::vector<Element> result;
    for(auto it = children_.begin();it != children_.end();++it)
    {
        if(it->GetClass().Matches(name))
            result.push_back(*it);
    }
    return result;
}
std::vector<Element*> Element::GetChildrenPtrByClassName(std::string name)
{
    std::vector<Element*> result;
    for(auto it = children_.begin();it != children_.end();++it)
    {
        if(it->GetClass().Matches(name))
            result.push_back(&(*it));
    }
    return result;
}
std::vector<Element> Element::GetChildrenById(std::string id)
{
    std::vector<Element> result;
    for(auto it = children_.begin();it != children_.end();++it)
    {
        if(it->GetId().GetValue() == id)
            result.push_back(*it);
    }
    return result;
}
std::vector<Element*> Element::GetChildrenPtrById(std::string id)
{
    std::vector<Element*> result = std::vector<Element*>();
    for(auto it = children_.begin();it != children_.end();++it)
    {
        if(it->GetId().GetValue() == id)
            result.push_back(&(*it));
    }
    return result;
}
Element Element::GetFirstChild()
{
    return children_.size() > 0 ? children_.front() : Element();
}
Element* Element::GetFirstChildPtr()
{
    return children_.size() > 0 ? &(*children_.begin()) : nullptr;
}
Element Element::GetChildAt(unsigned int position)
{
    return children_.size() > position ? children_[position] : Element();
}
Element* Element::GetChildPtrAt(unsigned int position)
{
    return children_.size() > position ? &(*(children_.begin()+position)) : nullptr;
}
Element Element::GetLastChild()
{
    return children_.size() > 0 ? children_.back() : Element();
}
Element* Element::GetLastChildPtr()
{
    return children_.size() > 0 ? &(*(children_.end()-1)) : nullptr;
}
size_t Element::GetChildrenCount() { return children_.size(); }
std::vector<Attribute> Element::GetAttributes()
{
    std::vector<Attribute> result = attributes_;
    if(!style_.GetValue().empty()) result.insert(result.begin(), style_);
    if(!class_.GetValue().empty()) result.insert(result.begin(), class_);
    if(!id_.GetValue().empty()) result.insert(result.begin(), id_);

    return result;
}
Attribute Element::GetAttributeByName(std::string name)
{
    if(name == Class::GetStaticName()) return class_;
    if(name == Id::GetStaticName()) return id_;
    if(name == Style::GetStaticName()) return style_;

    for(auto it = attributes_.begin();it != attributes_.end();++it)
    {
        if(it->GetName() == name) return *it;
    }
    return Attribute();
}
bool Element::HasRightBrother()
{
    if(parent_ == nullptr) return false;
    for(size_t i = 0; i < parent_->GetChildrenCount();i++)
    {
        if(parent_->GetChildPtrAt(i) == this)
            return i+1 < parent_->GetChildrenCount();
    }
    return false;
}
Element* Element::GetRightBrotherPtr()
{
    if(parent_ == nullptr) return nullptr;
    for(size_t i = 0; i < parent_->GetChildrenCount();i++)
    {
        if(parent_->GetChildPtrAt(i) == this)
        {
            if(i+1 < parent_->GetChildrenCount())
                return parent_->GetChildPtrAt(i+1);
            else break;
        }
    }
    return nullptr;
}
//Setters
void Element::SetName(std::string name) { name_ = name; }
void Element::SetText(std::string text) { text_ = text; }
void Element::AddText(std::string text) { text_ += text; }
void Element::SetClass(Class newClass) { class_ = newClass; }
void Element::SetId(Id id) { id_ = id; }
void Element::SetStyle(Style style) { style_ = style; }

void Element::RemoveChildren()
{
    children_.clear();
}
void Element::RemoveChildAt(unsigned int position)
{
    if(position >= children_.size()) return;
    children_.erase(children_.begin()+position);
}
void Element::AddChild(Element child)
{
    children_.push_back(child);
    children_.back().parent_ = this;
}
void Element::AddChildAt(Element child, unsigned int position)
{
    if(position >= children_.size()) return;
    children_.insert(children_.begin()+position, child);
    children_[position].parent_ = this;
}
void Element::AddChildren(std::vector<Element> children)
{
    size_t prevSize = children_.size();
    children_.insert(children_.end(), children.begin(), children.end());
    for(auto it = children_.begin()+prevSize;it != children_.end();++it)
        it->parent_ = this;
}

void Element::RemoveAttributes()
{
    attributes_.clear();
    class_ = Class();
    id_ = Id();
    style_ = Style();
}
void Element::RemoveAttributeByName(std::string name)
{
    if(name == Class::GetStaticName())
    {
        class_ = Class();
        return;
    }
    if(name == Id::GetStaticName())
    {
        id_ = Id();
        return;
    }
    if(name == Style::GetStaticName())
    {
        style_ = Style();
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
        class_ = Class(attribute);
        return;
    }
    if(attribute.GetName() == Id::GetStaticName())
    {
        id_ = Id(attribute);
        return;
    }
    if(attribute.GetName() == Style::GetStaticName())
    {
        style_ = Style(attribute);
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

std::vector<Element> Element::Find(std::string query)
{
    return Search::Find(*this, query);
}

std::vector<Element*> Element::FindPtr(std::string query)
{
    return Search::FindPtr(this, query);
}


//Protected member functions
void Element::SetDefaultValues()
{
    name_       = std::string();
    text_       = std::string();
    children_   = std::vector<Element>();
    parent_     = nullptr;
    attributes_ = std::vector<Attribute>();
    class_      = Class();
    id_         = Id();
    style_      = Style();
}
}

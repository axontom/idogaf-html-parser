/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef ELEMENT_H
#define ELEMENT_H

#include <new>
#include <string>
#include <vector>
#include "attribute.h"
#include "class.h"
#include "id.h"
#include "style.h"

namespace idogaf
{
class Element
{
    public:
        /** Default constructor */
        Element();
        /** Name-only contructor

            Constructs an Element object with a given tag name.

            @param name Tag name of the element.
        */
        Element(std::string name);
        /** Name-parent contructor

            Constructs an Element object with a given tag name
            as a child to a specified parent.

            @param name Tag name of the element.
            @param parent Parent for the element.
        */
        Element(std::string name, Element* parent);
        /** Full constructor

            Constructs an Element object,
            setting custom values to all memeber variables.
            If attributes vector contains attribute with name
            class, id or style, then corresponding member variables
            are set automatically.

            @param name Tag name of the element.

            @param text Text to store inside this element.

            @param children Vector of pointers to children elements.

            @param parent Parent for the element.

            @param attributes Vector of attributes for the element.
        */
        Element(std::string name, std::string text,
                std::vector<Element*> children, Element* parent,
                std::vector<Attribute> attributes);
        /** Common-attributes constructor

            Constructs an Element object with a given name, text, parent,
            children as well as class, id and style attributes.

            @param name Tag name of the element.

            @param text Text to store inside this element.

            @param children Vector of pointers to children elements.

            @param parent Parent for the element.

            @param css_class Css class for the element.

            @param id Id for the element.

            @param style Style for the element.
        */
        Element(std::string name, std::string text,
                std::vector<Element*> children, Element* parent,
                Class css_class, Id id, Style style);
        /** Copy constructor

            Deleted. Operate on pointers instead.

            @param other Object to copy from
         */
        Element(const Element& other) = delete;
        /** Assignment operator

            Deleted. Operate on pointers instead.

            @param other Object to assign from
            @return A reference to this
         */
        Element& operator=(const Element& other) = delete;
        /** Destroying deallocation operator

            Enables using destructor during deletion of heap-allocated objects.

            @param element Pointer to this object.
        */
        void operator delete(Element* element, std::destroying_delete_t);

        //Getters
        /** Get tag name of this element
            @return Tag name of this element
            or an empty string if name has not been set.
        */
        std::string             GetName();
        /** Get text contained by this element.
            @return Text contained by this element
            or an empty string if the text has not been set.
        */
        std::string             GetText();
        /** Get pointer to the parent of this element
            @return A pointer to the parent
            or nullptr if the parent has not been set.
        */
        Element*                GetParent();
        /** Get 'class' attribute of this element
            @return Class object matching this elements css class
            or nullptr if this element has no class attribute.
        */
        Class                   GetClass();
        /** Get 'id' attribute of this element
            @return Id object matching this elements id
            or nullptr if this element has no id attribute.
        */
        Id                      GetId();
        /** Get 'style' attribute of this element
            @return Style object matching this elements styles
            or nullptr if this element has no style attribute.
        */
        Style                   GetStyle();
        /** Get children of this element
            @return Vector containing pointers to all children of this element
            or an empty vector if this element has no children.
        */
        std::vector<Element*>   GetChildren();
        /** Get children of this element by tag name.

            Finds and returns every child matching given name.
            The search is case sensitive.

            @param name Name of the child to find.
            @return Vector containing pointers to all children
            of this element matching given name
            or an empty vector if this element has no children
            matching given name.
        */
        std::vector<Element*>   GetChildrenByTagName(std::string name);
        /** Get children of this element by class name.

            Finds and returns every child matching given css class.
            The search is case sensitive.

            @param name Class to find children by.
            @return Vector containing pointers to all children
            of this element matching given class name
            or an empty vector if this element has no children
            matching given class name.
        */
        std::vector<Element*>   GetChildrenByClassName(std::string name);
        /** Get children of this element by id.

            Finds and returns every child matching given id.
            The search is case sensitive.

            @param id Id to check children for.
            @return Vector containing pointers to all children
            of this element matching given id
            or an empty vector if this element has no children
            matching given id.
        */
        std::vector<Element*>   GetChildrenById(std::string id);
        /** Get first child of this element
            @return Pointer to the first child or nullptr
            if this element has no children.
        */
        Element*                GetFirstChild();
        /** Get pointer to a child at a given position
            @param position Position of the child.
            @return Pointer to child at requested position
            or nullptr if number of children this element has is
            smaller (or equal to) then requested position.
        */
        Element*                GetChildAt(unsigned int position);
        /** Get pointer to the last child of this element
            @return Pointer to the last child or nullptr
            if this element has no children.
        */
        Element*                GetLastChild();
        /** Get number of children this element has.
            @return Number of children this element has.
        */
        unsigned int            GetChildrenCount();
        /** Get all attributes of this element
            @return Vector containing all of this elements attributes
            (class, id and style included). Empty vector if this element
            has no attributes.
        */
        std::vector<Attribute>  GetAttributes();
        /** Get this elements attribute by name
            @return Attribute object containing attribute matching given name
            or nullptr if a matching attribute has not been found.
        */
        Attribute               GetAttributeByName(std::string name);


        //Setters

        /** Set this elements name
            @param name New name for this element.
        */
        void                    SetName(std::string name);
        /** Set text contained by this element
            @param text Text to set.
        */
        void                    SetText(std::string text);
        /** Add text contained by this element

            Adds new text at the end of already existing text.

            @param text Text to add.
        */
        void                    AddText(std::string text);
        /** Set new parent element for this element

            Sets given element as a parent to this element.
            This element receives a pointer to the given element
            and the given element receives pointer to this element as a child.
            This element is added as the new parents last child.
            If this element already had a parent, then the preious parent
            will lose a pointer to this element.
            If this child already is a part of the new parents children vector
            then it's not added a second time.

            @param parent Pointer to an existing element to set as a parent.
        */
        void                    SetParent(Element* parent);
        /** Remove parent from this element

            Removes a pointer to the parent element from this.
            Parents pointer to this element is also removed.
        */
        void                    RemoveParent();
        /** Set new css class attribute for this element
            @param newClass Class attribute to set.
        */
        void                    SetClass(Class newClass);
        /** Set new id attribute for this element
            @param id Id attribute to set.
        */
        void                    SetId(Id id);
        /** Set new style attribute for this element
            @param style Style attribute to set.
        */
        void                    SetStyle(Style style);

        /** Remove all children of this element

            Removes all children elements. This will not delete children
            elements objects, only connections between this element and
            children elements (this children pointers and every childs
            parent pointer.
        */
        void                    RemoveChildren();
        /** Remove child element at a given position

            Removes child (a pointer) from this elements children vector.
            Does not delete childs element object, but remove childs parent
            pointer. If given position is invalid (is greater or
            equal to vectors size) nothing happens.

            @param position Position of the child in this elements children
            vector. This corresponds with top to bottom order in html code.
            Indexing is zero-based.
        */
        void                    RemoveChildAt(unsigned int position);
        /** Add child element to this element

            Adds child at the end of this elements children vector.
            If a given pointer equals nullptr it won't be added.
            If a given child is already a child of this element
            it won't be added.
            The child will receive a pointer to this as parent
            and any connection from the child to the previous parent
            will be removed.

            @param child Pointer to a child element to add.
        */
        void                    AddChild(Element* child);
        /** Add child to this element at a given position

            Adds child before an element at a given position in this
            elements children vector. If a given pointer equals nullptr
            it won't be added. If given position is invalid
            (is greater or equal to vectors size) nothing happens.
            If a given child is already a child of this element
            it won't be added.
            The child will receive a pointer to this as parent
            and any connection from the child to the previous parent
            will be removed.

            @param child Pointer to a child element to add.
            @param position Position to add a child at in this elements children
            vector. This corresponds with top to bottom order in html code.
            Indexing is zero-based.
        */
        void                    AddChildAt(Element* child,
                                           unsigned int position);
        /** Add children from a given vector

            Adds children from a given vector to the end of this elements
            children vector. Every child also receives a pointer to this
            element as parent. If any child in a given vector already has
            a parent (including this element as parent), then every connection
            to that parent will be removed first.

            @param children Vector of pointers to the Element objects of
            children to add.
        */
        void                    AddChildren(std::vector<Element*> children);

        /** Remove all attributes from this element */
        void                    RemoveAttributes();
        /** Remove attribute from this element by name

            @param name Name of the attribute to remove
        */
        void                    RemoveAttributeByName(std::string name);
        /** Add an attribute to this element

            Adds a given attribute to this element. If this element already
            has an attribute equal to the given attributes, previous attribute
            will be swapped for the new one.

            @param attribute Attribute to add
        */
        void                    AddAtrribute(Attribute attribute);


    protected:
        std::string             name_;
        std::string             text_;
        std::vector<Element*>   children_;
        Element*                parent_;
        std::vector<Attribute>  attributes_;
        Class                   class_;
        Id                      id_;
        Style                   style_;

        /** Initializes member variables and sets them to default values

            Default values for variables:
            name_       -   empty string
            text_       -   empty string
            children_   -   empty vector
            parent_     -   nullptr
            attributes_ -   empty vector
            class_      -   nullptr
            id_         -   nullptr
            style_      -   nullptr
        */
        void                    SetDefaultValues();

    private:
        /** Private destructor

            It prevents stack allocation - Element object should only be
            initialized using 'new' operator.
        */
        ~Element() = default;

};
}

#endif // ELEMENT_H

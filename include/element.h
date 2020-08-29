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
        /** Full constructor

            Constructs an Element object,
            setting custom values to all memeber variables (excluding the parent
            pointer). If attributes vector contains attribute with name
            class, id or style, then corresponding member variables
            are set automatically.

            @param name Tag name of the element.

            @param text Text to store inside this element.

            @param children Vector of children elements.

            @param attributes Vector of attributes for the element.
        */
        Element(std::string name, std::string text,
                std::vector<Element> children, std::vector<Attribute> attributes);
        /** Common-attributes constructor

            Constructs an Element object with a given name, text and
            children as well as class, id and style attributes.

            @param name Tag name of the element.

            @param text Text to store inside this element.

            @param children Vector of children elements.

            @param css_class Css class for the element.

            @param id Id for the element.

            @param style Style for the element.
        */
        Element(std::string name, std::string text,
                std::vector<Element> children, Class css_class, Id id, Style style);
        /** Copy constructor

            Creates a copy of a given element including copies of the children
            elements, but not the parent element (this copy will have no parent).

            @param other Object to copy from
         */
        Element(const Element& other);
        /** Assignment operator

            Copies values of given elements member variables including copies of
            the children elements, but not the parent element
            (this will have no parent).

            @param other Object to assign from
            @return A reference to this
         */
        Element& operator=(const Element& other);
        /** Default destructor */
        ~Element() = default;

        //Getters
        /** Get copy of this element

            @return Object created with copy contructor based on this element.
        */
        Element                 Copy();
        /** Check if this element is empty

            @return True if this element has no name, text, attributes
            and children.
        */
        bool                    Empty();
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

            Get Class object of this element. If class for this element
            has not been set, returns an empty Class object (with no value).

            @return Class object matching this elements css class.
        */
        Class                   GetClass();
        /** Get 'id' attribute of this element

            Get Id object of this element. If id for this element
            has not been set, returns an empty Id object (with no value).

            @return Id object matching this elements id.
        */
        Id                      GetId();
        /** Get 'style' attribute of this element

            Get Style object of this element. If style for this element
            has not been set, returns an empty Style object (with no value).

            @return Style object matching this elements css style.
        */
        Style                   GetStyle();
        /** Get children of this element
            @return Vector containing copies of all children of this element
            or an empty vector if this element has no children.
        */
        std::vector<Element>   GetChildren();
        /** Get pointers to the children of this element

            Get pointers to every children of this element. Remember that any
            action resulting in resizing/rearranging of this elements children
            vector may invalidate those pointers. Use with caution.

            @return Vector containing pointers to all children of this element
            or an empty vector if this element has no children.
        */
        std::vector<Element*>   GetChildrenPtr();
        /** Get children of this element by tag name.

            Finds and returns copy of every child matching given name.
            The search is case sensitive.

            @param name Name of the child to find.
            @return Vector containing copies of all children
            of this element matching given tag name
            or an empty vector if this element has no children
            matching given name.
        */
        std::vector<Element>   GetChildrenByTagName(std::string name);
        /** Get children of this element by tag name.

            Finds and returns pointers to every child matching given name.
            The search is case sensitive. Remember that any
            action resulting in resizing/rearranging of this elements children
            vector may invalidate those pointers. Use with caution.

            @param name Name of the child to find.
            @return Vector containing pointers to all children
             of this element matching given tag name
            or an empty vector if this element has no children
            matching given name.
        */
        std::vector<Element*>   GetChildrenPtrByTagName(std::string name);
        /** Get children of this element by class name.

            Finds and returns copies of every child matching given css class.
            The search is case sensitive.

            @param name Class to find children by.
            @return Vector containing copies of all children
            of this element matching given class name
            or an empty vector if this element has no children
            matching given class name.
        */
        std::vector<Element>   GetChildrenByClassName(std::string name);
        /** Get children of this element by class name.

            Finds and returns pointers to every child matching given css class.
            The search is case sensitive. Remember that any
            action resulting in resizing/rearranging of this elements children
            vector may invalidate those pointers. Use with caution.

            @param name Class to find children by.
            @return Vector containing pointers to all children
            of this element matching given class name
            or an empty vector if this element has no children
            matching given class name.
        */
        std::vector<Element*>   GetChildrenPtrByClassName(std::string name);
        /** Get children of this element by id.

            Finds and returns copies of every child matching given id.
            The search is case sensitive.

            @param id Id to check children for.
            @return Vector containing copies of all children
            of this element matching given id
            or an empty vector if this element has no children
            matching given id.
        */
        std::vector<Element>   GetChildrenById(std::string id);
        /** Get children of this element by id.

            Finds and returns pointers to every child matching given id.
            The search is case sensitive. Remember that any
            action resulting in resizing/rearranging of this elements children
            vector may invalidate those pointers. Use with caution.

            @param id Id to check children for.
            @return Vector containing pointers to all children
            of this element matching given id
            or an empty vector if this element has no children
            matching given id.
        */
        std::vector<Element*>   GetChildrenPtrById(std::string id);
        /** Get first child of this element
            @return Copy of the first child or an empty element
            if this element has no children.
        */
        Element                 GetFirstChild();
        /** Get first child of this element
            @return Pointer to the first child or nullptr
            if this element has no children.
        */
        Element*                GetFirstChildPtr();
        /** Get copy of the child at a given position
            @param position Position of the child.
            @return Copy of the child at a requested position
            or an empty element if number of children this element has is
            smaller or equal to the requested position.
        */
        Element                 GetChildAt(unsigned int position);
        /** Get pointer to a child at a given position
            @param position Position of the child.
            @return Pointer to child at requested position
            or nullptr if number of children this element has is
            smaller or equal to the requested position.
        */
        Element*                GetChildPtrAt(unsigned int position);
        /** Get copy of the last child of this element
            @return Copy of the last child or an empty element
            if this element has no children.
        */
        Element                 GetLastChild();
        /** Get pointer to the last child of this element
            @return Pointer to the last child or nullptr
            if this element has no children.
        */
        Element*                GetLastChildPtr();
        /** Get number of children this element has.
            @return Number of children this element has.
        */
        size_t                  GetChildrenCount();
        /** Get all attributes of this element
            @return Vector containing all of this elements attributes
            (class, id and style included). Empty vector if this element
            has no attributes.
        */
        std::vector<Attribute>  GetAttributes();
        /** Get this elements attribute by name
            @return An Attribute object containing attribute matching
            given name or an empty attribute if a matching attribute
            has not been found.
        */
        Attribute               GetAttributeByName(std::string name);
        /** Check if this element has brother on the right
            @return True if it has right brother, false otherwise.
        */
        bool                    HasRightBrother();
        /** Get this elements right brother

            @return Pointer to it's right brother or nullptr if it has no
            brother on the right side.
        */
        Element*                GetRightBrotherPtr();

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
        */
        void                    RemoveChildren();
        /** Remove child element at a given position

            Removes child from this elements children vector.
            If given position is invalid (is greater or
            equal to vectors size) nothing happens.

            @param position Position of the child in this elements children
            vector. This corresponds with top to bottom order in html code.
            Indexing is zero-based.
        */
        void                    RemoveChildAt(unsigned int position);
        /** Add child element to this element

            Adds child at the end of this elements children vector.
            The child is given a pointer to this element as it's parent.

            @param child Child element to add.
        */
        void                    AddChild(Element child);
        /** Add child to this element at a given position

            Adds child before an element at a given position in this
            elements children vector. If a given pointer equals nullptr
            it won't be added. If given position is invalid
            (is greater or equal to vectors size) nothing happens.
            The child will receive a pointer to this as it's parent.

            @param child Pointer to a child element to add.
            @param position Position to add a child at in this elements children
            vector. This corresponds with top to bottom order in html code.
            Indexing is zero-based.
        */
        void                    AddChildAt(Element child,
                                           unsigned int position);
        /** Add children from a given vector

            Adds children from a given vector to the end of this elements
            children vector. Every child also receives a pointer to this
            element as parent.

            @param children Vector of the Element objects to add as children.
        */
        void                    AddChildren(std::vector<Element> children);

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

        //Other
        /** Find elements in a tree starting from this element.

            This function uses CSS selectors to search for elements
            in a tree starting from this element. Pseudo-classes and
            pseudo-elements are not supported right now. If a query matches
            an element twice (i.e. "div, .xxx" matches <div class="xxx">)
            then it will be included only once in a result vector
            (it won't be duplicated).

            @param query CSS selector query.
            @return Vector containg every element matching given query.
        */
        std::vector<Element>   Find(std::string query);
        /** Find elements in a tree

            This function uses CSS selectors to search for elements
            in a tree starting from this element. Pseudo-classes and
            pseudo-elements are not supported right now.
            If a query matches an element twice
            (i.e. "div, .xxx" matches <div class="xxx">) then it will
            be included only once in a result vector (it won't be duplicated).
            Warning: Due to operating on pointers, if during this function
            execution the tree is modified (possibly resulting in the
            invalidation of some pointers), the result of the function is
            undefined and possibility of a segmentation fault exists.
            Warning: Currently this will also search in this elements right
            siblings and it's ancestors right siblings and their children.
            Use Find() for stable results.

            @param query CSS selector query.
            @return Vector containg pointers to the elements matching given query.
        */
        std::vector<Element*> FindPtr(std::string query);


    protected:
        std::string             name_;
        std::string             text_;
        std::vector<Element>    children_;
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
            class_      -   empty class
            id_         -   empty id
            style_      -   empty style
        */
        void                    SetDefaultValues();
};
}

#endif // ELEMENT_H

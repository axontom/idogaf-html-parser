/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef ELEMENT_H
#define ELEMENT_H

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
            @param other Object to copy from
         */
        Element(const Element& other);
        /** Default destructor */
        virtual ~Element();
        /** Assignment operator
            @param other Object to assign from
            @return A reference to this
         */
        Element& operator=(const Element& other);

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
        void                    SetName(std::string name);
        void                    SetText(std::string text);
        void                    AddText(std::string text);
        void                    SetParent(Element* parent);
        void                    SetClass(Class newClass);
        void                    SetId(Id id);
        void                    SetStyle(Style style);

        void                    RemoveChildren();
        void                    RemoveChildAt(unsigned int position);
        void                    AddChild(Element* child);
        void                    AddChildAt(Element* child,
                                           unsigned int position);
        void                    AddChildren(std::vector<Element*> children);

        void                    RemoveAttributes();
        void                    RemoveAttributeByName(std::string name);
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
};
}

#endif // ELEMENT_H

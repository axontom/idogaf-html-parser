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
        std::string             GetName();
        std::string             GetText();
        Element*                GetParent();
        std::vector<Element*>   GetChildren();
        std::vector<Element*>   GetChildrenByTagName(std::string name);
        std::vector<Element*>   GetChildrenByClassName(std::string name);
        std::vector<Element*>   GetChildrenById(std::string id);
        Element*                GetFirstChild();
        Element*                GetChildAt(unsigned int position);
        Element*                GetLastChild();
        unsigned int            GetChildrenCount();
        std::vector<Attribute>  GetAttributes();
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

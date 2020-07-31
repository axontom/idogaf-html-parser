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
        /** Default destructor */
        virtual ~Element();
        /** Copy constructor
            @param other Object to copy from
         */
        Element(const Element& other);
        /** Assignment operator
            @param other Object to assign from
            @return A reference to this
         */
        Element& operator=(const Element& other);

        //Getters
        std::string             GetName();
        std::string             GetText();
        Element&                GetParent();
        std::vector<Element&>   GetChildren();
        std::vector<Element&>   GetChildrenByTagName(std::string name);
        std::vector<Element&>   GetChildrenByClassName(std::string name);
        std::vector<Element&>   GetChildrenById(std::string id);
        Element&                GetFirstChild();
        Element&                GetChildAt(unsigned int position);
        Element&                GetLastChild();
        unsigned int            GetChildrenCount();
        std::vector<Attribute>  GetAttributes();
        Attribute               GetAttributeByName(std::string name);


        //Setters
        void                    SetName(std::string name);
        void                    SetText(std::string text);
        void                    AddText(std::string text);
        void                    SetParent(Element& parent);
        void                    SetClass(Class newClass);
        void                    SetId(Id id);
        void                    SetStyle(Style style);

        void                    RemoveChildren();
        void                    RemoveChildAt(unsigned int position);
        void                    AddChild(Element& child);
        void                    AddChildAt(Element& child,
                                           unsigned int position);
        void                    AddChildren(std::vector<Element&> children);

        void                    RemoveAttributes();
        void                    RemoveAttributeByName(std::string name);
        void                    AddAtrribute(Attribute attribute);


    protected:
        std::string             name_;
        std::string             text_;
        Element&                parent_;
        std::vector<Element&>   children_;
        std::vector<Attribute>  attributes_;
        Class&                  class_;
        Id&                     id_;
        Style&                  style_;

    private:
};
}

#endif // ELEMENT_H

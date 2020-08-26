/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include "element.h"

namespace idogaf
{
class Document
{
    public:
        /** Default constructor */
        Document();
        /** Default destructor */
        ~Document() = default;
        /** Copy constructor
            @param other Object to copy from
         */
        Document(const Document& other);
        /** Assignment operator
            @param other Object to assign from
            @return A reference to this
         */
        Document& operator=(const Document& other);

        //Getters
        /** Get doctype of this document

            @return Doctype of this document or an empty string if the doctype
            has not been set.
        */
        std::string GetDoctype();
        /** Get the root element of the document

            @return Copy of the root element of this document, empty element if
            the root element has not been set.
        */
        Element     GetRoot();
        /** Get the root element of the document

            @return Pointer to the root element of this document, nullptr if
            the root element has not been set.
        */
        Element*    GetRootPtr();
        /** Check if document is empty
            @return True if root and doctype were not set, False otherwise.
            */
        bool        Empty();

        //Setters
        /** Set the root element of this document

            Add given element as a new root of this document.
            Removes any parent connections from a given element.

            @param root Pointer to the element to be set as root.
        */
        void        SetRoot(Element root);
        /** Set doctype of this document

            @param doctype Doctype to set.
        */
        void        SetDoctype(std::string doctype);

    protected:
        Element     root_;
        std::string doctype_;

    private:
};
}

#endif // DOCUMENT_H

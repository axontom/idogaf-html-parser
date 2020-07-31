/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "element.h"

namespace idogaf
{
class Document
{
    public:
        /** Default constructor */
        Document();
        /** Default destructor */
        virtual ~Document();
        /** Copy constructor
            @param other Object to copy from
         */
        Document(const Document& other);
        /** Assignment operator
            @param other Object to assign from
            @return A reference to this
         */
        Document& operator=(const Document& other);

    protected:
        Element&    root_;

    private:
};
}

#endif // DOCUMENT_H

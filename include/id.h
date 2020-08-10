/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef ID_H
#define ID_H

#include "attribute.h"

namespace idogaf
{
class Id : public Attribute
{
    public:
        /** Default constructor */
        Id();
        /** Default destructor */
        virtual ~Id();
        /** Copy constructor
            @param other Object to copy from.
         */
        Id(const Id& other);
        /** Attribute-based constructor

            Copies values from the attribute.

            @param attribute Attribute to copy values from.
        */
        Id(const Attribute& attribute);
        /** Assignment operator
            @param other Object to assign from.
            @return A reference to this.
         */
        Id& operator=(const Id& other);

        static std::string GetStaticName();

    protected:

    private:
};
}

#endif // ID_H

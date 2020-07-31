/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

namespace idogaf
{
class Attribute
{
    public:
        /** Default constructor */
        Attribute();
        /** Default destructor */
        virtual ~Attribute();
        /** Copy constructor
            @param other Object to copy from
         */
        Attribute(const Attribute& other);
        /** Assignment operator
            @param other Object to assign from
            @return A reference to this
         */
        Attribute& operator=(const Attribute& other);

    protected:
        std::string     name_;
        std::string     content_;

    private:
};
}

#endif // ATTRIBUTE_H

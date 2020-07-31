/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef CLASS_H
#define CLASS_H

#include <attribute.h>

namespace idogaf
{
class Class : public Attribute
{
    public:
        /** Default constructor */
        Class();
        /** Default destructor */
        virtual ~Class();
        /** Copy constructor
            @param other Object to copy from
         */
        Class(const Class& other);
        /** Assignment operator
            @param other Object to assign from
            @return A reference to this
         */
        Class& operator=(const Class& other);

    protected:
        std::vector<std::string> classes_;

    private:
};
}

#endif // CLASS_H

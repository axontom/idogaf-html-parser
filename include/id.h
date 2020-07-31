/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef ID_H
#define ID_H

#include <atrribute.h>

namespace idogaf
{
class Id : public Atrribute
{
    public:
        /** Default constructor */
        Id();
        /** Default destructor */
        virtual ~Id();
        /** Copy constructor
         *  \param other Object to copy from
         */
        Id(const Id& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        Id& operator=(const Id& other);

    protected:

    private:
};
}

#endif // ID_H

/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef SCRIPT_H
#define SCRIPT_H

#include <element.h>

namespace idogaf
{
class Script : public Element
{
    public:
        /** Default constructor */
        Script();
        /** Default destructor */
        virtual ~Script();
        /** Copy constructor
            @param other Object to copy from
         */
        Script(const Script& other);
        /** Assignment operator
            @param other Object to assign from
            @return A reference to this
         */
        Script& operator=(const Script& other);

    protected:

    private:
};
}

#endif // SCRIPT_H

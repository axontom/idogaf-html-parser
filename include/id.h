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
    /** Default constructor

        Creates an object with no value.
    */
    Id();
    /** Copy constructor
        @param other Object to copy from.
     */
    Id(const Id& other);
    /** Attribute-based constructor

        Copies values from the attribute.

        @param attribute Attribute to copy values from.
    */
    Id(const Attribute& attribute);
    /** Default destructor */
    ~Id() = default;

    /** Assignment operator
        @param other Object to assign from.
        @return A reference to this.
     */
    Id& operator=(const Id& other);

    //Getters
    static std::string GetStaticName();

    //Setters
    /** Set this attributes name

        @ATT This function does nothing. It's here only for compatibility
        purposes.
    */
    void SetName(std::string name);

protected:

private:
};
}

#endif // ID_H

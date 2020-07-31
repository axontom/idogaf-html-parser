/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef STYLE_H
#define STYLE_H

#include <string>
#include <attribute.h>

namespace idogaf
{

/** Name-Value pair structure for storing css classes
*/
struct DStringPair
{
    std::string name;
    std::string value;
};

class Style : public Attribute
{
    public:
        /** Default constructor */
        Style();
        /** Default destructor */
        virtual ~Style();
        /** Copy constructor
            @param other Object to copy from
         */
        Style(const Style& other);
        /** Assignment operator
            @param other Object to assign from
            @return A reference to this
         */
        Style& operator=(const Style& other);

    protected:
        std::vector<DStringPair>    styles;

    private:
};
}

#endif // STYLE_H

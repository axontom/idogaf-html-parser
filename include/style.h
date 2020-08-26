/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef STYLE_H
#define STYLE_H

#include <string>
#include <vector>
#include "attribute.h"

namespace idogaf
{

/** Name-Value pair structure for storing css styles
*/
struct DStringPair
{
    std::string name = "";
    std::string value = "";
};

class Style : public Attribute
{
    public:
        /** Default constructor

            Creates an object with no value.
        */
        Style();
        /** Default destructor */
        virtual ~Style();
        /** Copy constructor
            @param other Object to copy from
         */
        Style(const Style& other);
        /** Attribute-based constructor

            Copies values from the attribute.

            @param attribute Attribute to copy values from.
        */
        Style(const Attribute& attribute);
        /** Assignment operator
            @param other Object to assign from
            @return A reference to this
         */
        Style& operator=(const Style& other);

        //Getters
        static std::string GetStaticName();

        //Setters
        /** Set this attributes name

            @ATT This function does nothing. It's here only for compatibility
            purposes.
        */
        void SetName(std::string name);

    protected:
        std::vector<DStringPair>    styles_;

        /** Parses string for css styles and adds them

            Given string is parsed for css styles. Every extracted style is
            added to styles_ vector and value_ variable.
            Name and value should of a style should be separated by ':'.
            Multiple styles should be separeted by ';'.
            Any whitespaces in names or values will be included.

            @param str String to parse.
            @return Number of successfully added styles.
        */
        unsigned int    ParseStringForStyles(std::string str);

    private:
};
}

#endif // STYLE_H

/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>
#include <vector>

namespace idogaf
{

class Attribute;

typedef std::vector<Attribute> Vector_A;

typedef std::vector<Attribute>::iterator Vector_A_it;

class Attribute
{
public:
    /** Default constructor

        Constructs an Attribute with no name and no value.
    */
    Attribute();
    /** Name-only contructor

        Constructs an Attribute object with a given name and no value.

        @param name Name for this Attribute.
    */
    Attribute(std::string name);
    /** Full contructor

        Constructs an Attribute with name and value specified.

        @param name Name for this Attribute.

        @param value Value for this attribute.
    */
    Attribute(std::string name, std::string value);

    /** Default destructor */
    ~Attribute() = default;
    /** Copy constructor

        @param other Object to copy from.
     */
    Attribute(const Attribute& other);
    /** Assignment operator

        @param other Object to assign from.
        @return A reference to this.
     */
    Attribute& operator=(const Attribute& other);

    //Getters
    /** Returns the name of the attribute

        @return Name of the attribute or
        an empty string if no name has been set.
    */
    std::string GetName() const;
    /** Returns the value of the attribute

        @return Data stored in attribute.
    */
    std::string GetValue() const;

    //Setters
    /** Sets the name of the attribute

        @param name Name to set.
    */
    void        SetName(std::string name);
    /** Sets the value of the attribute

        @param content Value to set.
    */
    void        SetValue(std::string value);

protected:
    std::string name_;
    std::string value_;

private:
};
}

#endif // ATTRIBUTE_H

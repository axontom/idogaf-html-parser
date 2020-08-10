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
        /** Attribute-based constuctor

            Constructs a Class object and asignes it classes by spliting
            given attributes value into class names
            (which should be separated by white spaces).
            Example: Attribute with value "c1 c2 c3" will result in
            Class object with classes c1, c2, and c3.

            @param attribute Attribute to copy name and value/classes from.
        */
        Class(const Attribute& attribute);
        /** Copy constructor
            @param other Object to copy from
         */
        Class(const Class& other);
        /** Default destructor */
        virtual ~Class();
        /** Assignment operator
            @param other Object to assign from
            @return A reference to this
         */
        Class& operator=(const Class& other);

        //Getters
        /** Get every class contained by this attribute in form of vector
            @return Vector of strings, with classes contained by this attribute.
        */
        std::vector<std::string> GetClassesInVector();
        static std::string GetStaticName();

        //Setters
        void SetName(std::string name) delete;

        //Other
        /** Checks if this attributes contains class of a given name.

            Compares given name with classes contained by this attributes.
            Comparison is case sensitive.

            @param className Name of class to match.
            @return True if any class contained by this attribute matches
            given name. False otherwise.
        */
        bool Matches(std::string className);

    protected:
        std::vector<std::string> classes_;

    private:
};
}

#endif // CLASS_H

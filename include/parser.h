/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include <string>
#include "attribute.h"
#include "document.h"
#include "element.h"

namespace idogaf
{
class Parser
{
    public:
        /** Default constructor */
        Parser();
        /** Default destructor */
        ~Parser() = default;
        /** Copy constructor
            @param other Object to copy from
         */
        Parser(const Parser& other);
        /** Assignment operator
            @param other Object to assign from
            @return A reference to this
         */
        Parser& operator=(const Parser& other);

        //Getters
        /** Get parsed document

            @return Pointer to the parsed document.
        */
        Document*   GetDocument();

        //Setters
        /** Set parsers silent mode

            Choose if parser should write to console about errors
            and notifications.

            @param silent Use true if you don't want the parser to write
            to console and false otherwise.
        */
        void        Silent(bool silent = false);

        //Other
        bool        Parse(const std::string& filename);
        bool        Parse(std::istream& stream);

    protected:
        bool        silent_;
        Document    document_;

        /** Read next html tag from stream

            Reads from stream until the end of next tag and return an Element
            object with a name and attributes of the next tag. If the Doctype
            tag is found, this function sets an apropriate parameter in the
            document_ variable. After this it will read until the end of the
            next tag. Every comment tag (<!-- -->) is ignored. If a text is
            found before the next tag it is set in a textOut parameter,
            whitespaces before and after the text are trimmed and multiple
            newline characters in a row are changed to a single one. If comment
            or a doctype tag was found between the text an additional newline
            will be added in it's place. If the next tag was an empty one
            (<tag/>) emptyOut is set to true. If the next tag was a closing tag
            (</tag>) then closeOut parameter is set to true. If a given stream
            ended before the next tag (eofbit was set) or failed,
            then this function returns nullptr.

            @param stream
            Reference to a stream to read from.

            @param emptyOut
            Output parameter, is set to true if found tag was empty (<tag/>),
            false otherwise.

            @param closeOut
            Output parameter, is set to true if found tag was a closing tag
            (<tag/>), false otherwise.

            @param textOut
            Output parameter, if any text was found before the next tag, this
            will contain it, otherwise it will be empty.

            @return Pointer to an Element object with the next tag,
            or nullptr if the stream ended or failed.
        */
        Element*    ReadNextTag(std::istream& stream, bool& emptyOut,
                                bool& closeOut, std::string& textOut);
        /** Parse tag for an element

            Parses a html tag in a given string for an Element object with
            a name and attributes if they exist. The given string should
            contain everything between '<' or '</' and '>' or '/>' signs.
            If an std::ios_base::failure exception is cought while extracting
            the name, this function returns nullptr. Otherwise it returns
            pointer to the new Element object. If an exception was cought
            and the parser doesn't run in a silent mode, then an apropriate
            message is written to stderr.

            @param tag String containing a tag to parse.
            @return Pointer to an Element object or nullptr if a function fails.
        */
        Element*    ParseTagForElement(const std:string& tag);
        /** Parse string for an attribute

            Parses string for an attribute, extracting it's name and value.
            The given string should be in a form of 'name="value"'
            (excluding ' character). If the string doesn't contain '=' character
            this function returns nullptr, otherwise it returns an Attribute
            object with the name created from part of the string to the left of
            the '=' sign and value from a right part, excluding the last
            character and the first character after '='.

            @param str String to parse.
            @return Attribute object or a nullptr, if given string doesn't
            contain '='.
        */
        Attribute   ParseStringForAttribute(const std::string& str);

    private:
};
}

#endif // PARSER_H

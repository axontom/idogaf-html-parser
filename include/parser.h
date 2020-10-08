/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include <ostream>
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
        @return Copy of the parsed document.
    */
    Document    GetDocument() const;
    /** Get parsed document
        @return Pointer to the parsed document.
    */
    Document*   GetDocumentPtr();
    bool        Silent() const;

    //Setters
    /** Set parsers silent mode

        Choose if parser should write to console about errors
        and notifications.

        @param silent Use true if you don't want the parser to write
        to console and false otherwise.
    */
    void        Silent(bool silent = false);

    //Other
    /** Parse html document from file

        Parses document to Document object. To retrieve parsed Document
        object use GetDocument().

        @param filename Name of the file to parse.
        @return True on success, False otherwise.
    */
    bool        Parse(const std::string& filename);
    /** Parse html document from stream

        Parses document to Document object. To retrieve parsed Document
        object use GetDocument().

        @param stream Stream to read from.
        @return True on success, False otherwise.
    */
    bool        Parse(std::istream& stream);
    /** Write current Document object to file

        Writes document object from document_ variable to file with a given
        filename.

        @param filename Name of the output file.
        @return True on success, False otherwise.
    */
    bool        WriteToFile(const std::string& filename);
    /** Write current Document object to stream

        @param stream Output stream to write to.
        @return True on success, False otherwise.
    */
    bool        WriteToStream(std::ostream& stream);

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

        @param linesOut
        Output parameter, returns number of lines read.

        @return An Element object with the next tag,
        or an empty element if the stream ended or failed.
    */
    Element     ReadNextTag(std::istream& stream, bool& emptyOut,
                            bool& closeOut, std::string& textOut,
                            size_t& linesOut);
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
        @return An Element object or an empty element if this function fails.
    */
    Element     ParseTagForElement(const std::string& tag);
    /** Parse string for an attribute

        Parses string for an attribute, extracting it's name and value.
        The given string should be in a form of 'name="value"'
        (excluding ' character). If the string doesn't contain '=' character
        this function returns an Attribute object with a name of a given
        string and no value, otherwise it returns an Attribute object
        with the name created from part of the string to the left of
        the '=' sign and value from a right part, excluding the last
        character and the first character after '='.

        @param str String to parse.
        @return An Attribute object.
    */
    Attribute   ParseStringForAttribute(const std::string& str);

    /** Write opening tag of an element to stream

        Write opening tag. If the tag has no children and no text,
        it is written as an empty tag. If it has text, but has no children
        then after the opening tag, the text is writen and it's closed by
        calling the WriteClosingTag function.

        @param element Pointer to an element object to write the tag of.
        @param stream Output stream to write to.
        @param indent Level of indentation (number of tabs to write
        before the tag).
    */
    void WriteOpeningTag(Element* element, std::ostream& stream,
                         unsigned int indent = 0);
    /** Write closing tag of an element to stream

        @param element Pointer to an element object to write the tag of.
        @param stream Output stream to write to.
        @param indent Level of indentation (number of tabs to write
        before the tag).
    */
    void WriteClosingTag(Element* element, std::ostream& stream,
                         unsigned int indent = 0);
    /** Get indentation as string

        Returns string containing a given number of tabs.

        @param level Level of indentation (number of tabs).
        @return String with an indentation.
    */
    std::string GetIndentation(unsigned int level) const;
    /** End with unexpected tag error

        Prints unexpected tag error message, if parser doesn't run in
        silent mode.

        @param tagName Name of the unexpected tag.
        @param line Line at which the unexpected tag was found.
        @return Always false.
    */
    bool UnexpectedTagError(const std::string& tagName, size_t line) const;
    /** End with document empty error

        Prints document empty error message, if parser doesn't run in
        silent mode.

        @return Always false.
    */
    bool DocumentEmptyError() const;

private:
};
}

#endif // PARSER_H

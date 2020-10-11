#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <string>
#include <vector>

namespace idogaf
{

/** Trim string from both sides

    Remove whitespaces from the begining and the end of the string.

    @param str String to trim.
    @return Trimmed string.
*/
std::string trim(const std::string& str);

/** Count '\n' characters in string

    @param str String to use.
    @return Number of '\n' characters.
*/
size_t countLines(const std::string& str);

/** Check for string in vector

    @param str String to search for.
    @param strVec Vector to search in.
    @return True if a string equal to str was found inside strVec,
            false otherwise.
*/
bool strInVector(const std::string& str, const std::vector<std::string>& strVec);

/** Check if closing tag can be omitted

    Checks if closing tag can be omitted if it is immediately followed by
    the element of a given name.

    @param Name of tag to check.
    @param nextTag Name of the next tag.
    @return True if the closing tag of the 'tag' can be omitted, false otherwise.
*/
bool omittClosingTag(const std::string& tag, const std::string& nextTag);

/** Check if closing tag can be omitted

    Checks if closing tag can be omitted if there is no more content
    in the parent element.

    @param Name of tag to check.
    @param parent Name of the parent tag.
    @return True if the closing tag of the 'tag' can be omitted, false otherwise.
*/
bool omittClosingTagNMC(const std::string& tag, const std::string& parent);


const std::vector<std::string> kSingletonTags = {
    "area", "base", "br", "col", "command", "embed", "hr", "img", "input",
    "keygen", "link", "meta", "param", "source", "track", "wbr" };
const std::vector<std::string> kpElementOptVec = {
    "address", "article", "aside", "blockquote", "dic", "dl", "fieldset",
    "footer", "form", "h1", "h2", "h3", "h4", "h5", "h6", "header", "hgroup",
    "hr", "main", "nav", "ol", "p", "pre", "section", "table", "ul" };
const std::vector<std::string> kOptCTagNMC = {
    "li", "dd", "rb", "rt", "rtc", "rp", "optgroup", "option", "tbody", "tfoot",
    "tr", "td", "th" };
}

#endif // MISC_H_INCLUDED

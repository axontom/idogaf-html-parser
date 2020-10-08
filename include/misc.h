#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <string>

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

/** Check for string in array

    @param str String to search for.
    @param strArray Array to search in.
    @param arrSize Size of the array.
    @return True if a string equal to str was found inside strArray,
            false otherwise.
*/
bool isInArray(const std::string& str, const std::string (&strArray)[],
               size_t arrSize);

const std::string kSingletonTags[] = {  "area", "base", "br", "col", "command",
                                        "embed", "hr", "img", "input", "keygen",
                                        "link", "meta", "param", "source",
                                        "track", "wbr" };
}

#endif // MISC_H_INCLUDED

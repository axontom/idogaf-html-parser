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

}

#endif // MISC_H_INCLUDED

#include "misc.h"

#include <ctype.h>

namespace idogaf
{
std::string trim(const std::string& str)
{
    size_t left = 0, right = 0;
    bool wsOnly = true;
    for(size_t i = 0; i < str.length(); i++)
    {
        if(!isspace(str[i]))
        {
            left = i;
            wsOnly = false;
            break;
        }
    }
    if(wsOnly) return std::string();
    for(long int i = str.length()-1; i >= 0; i--)
    {
        if(!isspace(str[i]))
        {
            right = i;
            break;
        }
    }
    return str.substr(left, right-left+1);
}
size_t countLines(const std::string& str)
{
    size_t lines = 0;
    for(size_t i = 0; i < str.length(); i++)
        if(str[i] == '\n') lines++;
    return lines;
}
bool isInArray(const std::string& str, const std::string (&strArray)[],
               size_t arrSize)
{
    for(size_t i = 0; i < arrSize; i++)
        if(strArray[i] == str) return true;
    return false;
}
bool omittClosingTag(const std::string& tag, const std::string& nextTag)
{
    if(tag == "li" || tag == "optgroup" || tag == "tr")
        return nextTag == tag;
    if(tag == "dt")
        return nextTag == "dt" || nextTag == "dd";
    if(tag == "dd")
        return nextTag == "dt" || nextTag == "dd";
    if(tag == "p")
        return isInArray(nextTag, kpElementOptArr,
                         sizeof(kpElementOptArr)/sizeof(std::string));
    if(tag == "rb" || tag == "rt" || tag == "rtc" || tag == "rp")
        return nextTag == "rb" || nextTag == "rt" ||
               nextTag == "rtc" || nextTag == "rp";
    if(tag == "option")
        return nextTag == "option" || nextTag == "optgroup";
    if(tag == "thead")
        return nextTag == "tbody" || nextTag == "tfoot";
    if(tag == "tbody")
        return nextTag == "tbody" || nextTag == "tfoot";
    if(tag == "tfoot")
        return nextTag == "tbody";
    if(tag == "td" || tag == "th")
        return nextTag == "td" || nextTag == "th";

    return false;
}
bool omittClosingTagNMC(const std::string& tag, const std::string& parent)
{
    if(tag == "p") return parent != "a";
    return isInArray(tag, kOptCTagNMC, sizeof(kOptCTagNMC)/sizeof(std::string));
}

}

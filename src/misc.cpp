#include <ctype.h>
#include "misc.h"

namespace idogaf
{
    std::string trim(const std::string& str)
    {
        size_t left = 0, right = 0;
        for(size_t i = 0; i < str.length(); i++)
        {
            if(!isspace(str[i]))
            {
                left = i;
                break;
            }
        }
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
}

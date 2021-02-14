#include "search.h"

#include <sstream>

#include "attribute.h"
#include "class.h"
#include "misc.h"

namespace idogaf
{

Vector_E Search::Find(Element root, const std::string& query)
{
    Vector_E result;
    Set_P resultSet;
    Set_P qResult;
    std::string _query = trim(query);
    //Count number of ',' in query
    size_t cnt = 1, pos = 0;
    while((pos = _query.find(',', pos)) != std::string::npos)
    {
        cnt++;
        pos++;
    }
    for(size_t i = 0, pos1 = 0; i < cnt; i++)
    {
        size_t pos2 = _query.find(',', pos1);
        std::string cmplx = trim(_query.substr(pos1, pos2-pos1));
        //in cmplx we have one of the complex queries
        //now process it
        bool first = true;
        qResult.clear();
        qResult.insert(&root);
        while(!cmplx.empty())
        {
            switch(cmplx[0])
            {
            case '.':
            case '#':
            {
                if(cmplx.length() <= 1) break;
                pos = FindSeparator(cmplx.substr(1));
                if(pos != std::string::npos) pos++;
                break;
            }
            case '[':
            {
                pos = cmplx.find(']');
                if(pos != std::string::npos) pos++;
                break;
            }
            default:
                pos = FindSeparator(cmplx);
            }
            if(first)
            {
                qResult = RunQuery(qResult, trim(cmplx.substr(0, pos)));
                first = false;
            }
            else
                qResult = CheckElements(qResult, trim(cmplx.substr(0, pos)));
            if(cmplx[pos] == ' ' || cmplx[pos] == '>' ||
                    cmplx[pos] == '+' || cmplx[pos] == '~')
            {
                qResult = ProcessSeparator(qResult, cmplx[pos]);
                pos++;
            }
            if(pos == std::string::npos)
                cmplx.clear();
            else
                cmplx = trim(cmplx.substr(pos));
        }
        resultSet.insert(qResult.begin(), qResult.end());
        pos1 = pos2 + 1;
    }
    for(Set_P_it it = resultSet.begin(); it != resultSet.end(); ++it)
        result.push_back(**it);
    return result;
}

Vector_P Search::FindPtr(Element* root, const std::string& query)
{
    Set_P result;
    Set_P qResult;
    std::string _query = trim(query);
    //Count number of ',' in query
    size_t cnt = 0, pos = 0;
    while((pos = _query.find(',', pos)) != std::string::npos)
    {
        cnt++;
        pos++;
    }
    for(size_t i = 0, pos1 = 0; i < cnt; i++)
    {
        size_t pos2 = _query.find(',', pos1);
        std::string cmplx = trim(_query.substr(pos1, pos2-pos1));
        //in cmplx we have one of the complex queries
        //now process it
        bool first = true;
        qResult.clear();
        qResult.insert(root);
        while(!cmplx.empty())
        {
            switch(cmplx[0])
            {
            case '.':
            case '#':
            {
                if(cmplx.length() <= 1) break;
                pos = FindSeparator(cmplx.substr(1, std::string::npos));
                if(pos != std::string::npos) pos++;
                break;
            }
            case '[':
            {
                pos = cmplx.find(']');
                if(pos != std::string::npos) pos++;
                break;
            }
            default:
                pos = FindSeparator(cmplx);
            }
            if(first)
            {
                qResult = RunQuery(qResult, trim(cmplx.substr(0, pos)));
                first = false;
            }
            else
                qResult = CheckElements(qResult, trim(cmplx.substr(0, pos)));
            if(cmplx[pos] == ' ' || cmplx[pos] == '>' ||
                    cmplx[pos] == '+' || cmplx[pos] == '~')
            {
                qResult = ProcessSeparator(qResult, cmplx[pos]);
                pos++;
            }
            cmplx = trim(cmplx.substr(pos, std::string::npos));
        }
        result.insert(qResult.begin(),qResult.end());
        pos1 = pos2 + 1;
    }
    return Vector_P(result.begin(), result.end());
}

Vector_E Search::FindInVector(Vector_E vec, const std::string& query)
{
    Vector_E result, partial;
    for(Vector_E_it it = vec.begin(); it != vec.end(); ++it)
    {
        partial = Find(*it, query);
        result.insert(result.end(), partial.begin(), partial.end());
    }
    return result;
}

//Private member functions
Set_P Search::RunQuery(Set_P elements, const std::string& query)
{
    Set_P result;
    for(Set_P_it it = elements.begin(); it != elements.end(); ++it)
    {
        Element* a = *it;
        bool running = true;
        while(running)
        {
            if(CheckElement(a, query))
                result.insert(a);
            if(a->GetChildrenCount() > 0)
                a = a->GetFirstChildPtr();
            else if(a->GetParent() == nullptr) break;
            else
            {
                while(true)
                {
                    if(a->GetParent() == nullptr)
                    {
                        running = false;
                        break;
                    }
                    else if(a->HasRightBrother())
                    {
                        a = a->GetRightBrotherPtr();
                        break;
                    }
                    else a = a->GetParent();
                }
            }
        }
    }
    return result;
}

bool Search::CheckElement(Element* element, const std::string& query)
{
    std::string _query = query;
    if(_query.empty()) return false;
    if(element == nullptr) return false;

    switch(_query.front())
    {
    case '.':
        return _ofClass(element, _query.substr(1));
    case '#':
        return _hasId(element, _query.substr(1));
    case '[':
    {
        if(_query.back() != ']') return false;
        _query = _query.substr(1, _query.length()-2);
        size_t pos = _query.find('=');
        if(pos == std::string::npos)
            return _hasAttribute(element, trim(_query));
        else
        {
            if(pos == 0 || pos == _query.length()-1) return false;
            switch(_query[pos-1])
            {
            case '~':
                return _hasWord(element, trim(_query.substr(0,pos-1)),
                                trim(_query.substr(pos+1)));
            case '|':
                return _startingWith(element, trim(_query.substr(0,pos-1)),
                                     trim(_query.substr(pos+1)));
            case '^':
                return _beginingWith(element, trim(_query.substr(0,pos-1)),
                                     trim(_query.substr(pos+1)));
            case '$':
                return _endingWith(element, trim(_query.substr(0,pos-1)),
                                   trim(_query.substr(pos+1)));
            case '*':
            {
                if(!trim(_query.substr(0,pos-1)).empty())
                    return _hasSubstr(element, trim(_query.substr(0,pos-1)),
                                      trim(_query.substr(pos+1)));
            }
            default:
                return _hasValue(element, trim(_query.substr(0,pos)),
                                 trim(_query.substr(pos+1)));
            }
        }
    }
    default:
        return element->GetName() == _query;
    }
}

Set_P Search::CheckElements(Set_P elements, const std::string& query)
{
    Set_P result;
    for(Set_P_it it = elements.begin(); it != elements.end(); ++it)
    {
        if(CheckElement(*it, query))
            result.insert(*it);
    }
    return result;
}

Set_P Search::ProcessSeparator(Set_P elements, char separator)
{
    switch(separator)
    {
    case ' ':
        return _inside(elements);
    case '>':
        return _child(elements);
    case '+':
        return _rBrother(elements);
    case '~':
        return _preceded(elements);
    }
    return Set_P();
}

size_t Search::FindSeparator(const std::string& query)
{
    size_t pos = query.find_first_of(" >+~.[#");
    if(pos == std::string::npos || query.length() <= pos+1) return pos;
    if(query[pos] == ' ')   //Handle spaces before >+~ signs
    {
        while(query[pos+1] == ' ') //skip multiple spaces
            pos++;
        if(query[pos+1] == '>' || query[pos+1] == '+' || query[pos+1] == '~')
            return pos+1;
    }
    return pos;
}

//Separators
Set_P Search::_inside(Set_P elements)
{
    Set_P result;
    for(Set_P_it it = elements.begin(); it != elements.end(); ++it)
    {
        Element* e = *it;
        while(true)
        {
            if(e != *it)
                result.insert(e);
            if(e->GetChildrenCount() > 0)
                e = e->GetFirstChildPtr();
            else
            {
                while(!e->HasRightBrother())
                {
                    if(e->GetParent() == nullptr || e->GetParent() == *it) break;
                    e = e->GetParent();
                }
                if(e->GetParent() == nullptr || e->GetParent() == *it) break;
                e = e->GetRightBrotherPtr();
            }
        }
    }
    return result;
}
Set_P Search::_child(Set_P elements)
{
    Set_P result;
    for(Set_P::iterator it = elements.begin(); it != elements.end(); ++it)
    {
        Vector_P vec = (*it)->GetChildrenPtr();
        result.insert(vec.begin(), vec.end());
    }
    return result;
}
Set_P Search::_rBrother(Set_P elements)
{
    Set_P result;
    for(Set_P::iterator it = elements.begin(); it != elements.end(); ++it)
    {
        if((*it)->HasRightBrother())
            result.insert((*it)->GetRightBrotherPtr());
    }
    return result;
}
Set_P Search::_preceded(Set_P elements)
{
    Set_P result;
    for(Set_P::iterator it = elements.begin(); it != elements.end(); ++it)
    {
        Element* e = *it;
        if(e->GetParent() == nullptr) continue;
        e = e->GetParent();
        for(size_t i = 0; i < e->GetChildrenCount(); i++)
        {
            Element* sibling = e->GetChildPtrAt(i);
            if(sibling == *it) break;
            result.insert(sibling);
        }
    }
    return result;
}

//Single selectors
bool Search::_ofClass(Element* e, const std::string& name)
{
    if(name == "*") return !e->GetClass().GetValue().empty();
    return e->GetClass().Matches(name);
}
bool Search::_hasId(Element* e, const std::string& name)
{
    if(name == "*") return !e->GetId().GetValue().empty();
    return e->GetId().GetValue() == name;
}
bool Search::_hasAttribute(Element* e, const std::string& name)
{
    if(name == "*") return !e->GetAttributes().empty();
    return !e->GetAttributeByName(name).GetName().empty();
}
bool Search::_hasValue(Element* e, const std::string& name,
                       const std::string& value)
{
    std::string _value = value;
    if(_value.empty()) return false;
    if(name == "*" && value == "*") !e->GetAttributes().empty();
    if(_value == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(_value.front() == '"' && _value.back() == '"' && _value.length() > 1)
        _value = value.substr(1,value.length()-2);
    if(name == "*")
    {
        Vector_A attributes = e->GetAttributes();
        for(Vector_A::iterator it = attributes.begin(); it != attributes.end(); ++it)
        {
            if(it->GetValue() == _value) return true;
        }
        return false;
    }
    return e->GetAttributeByName(name).GetValue() == _value;
}
bool Search::_hasWord(Element* e, const std::string& name,
                      const std::string& word)
{
    std::string _word = word;
    if(_word.empty()) return false;
    if(name == "*" && word == "*") !e->GetAttributes().empty();
    if(_word == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(_word.front() == '"' && _word.back() == '"' && _word.length() > 1)
        _word = _word.substr(1,_word.length()-2);
    Vector_A attributes;
    if(name == "*")
        attributes = e->GetAttributes();
    else
    {
        Attribute a = e->GetAttributeByName(name);
        if(a.GetName().empty()) return false;
        attributes.push_back(a);
    }
    std::string buffer;
    for(Vector_A_it it = attributes.begin(); it != attributes.end(); ++it)
    {
        std::stringstream ss(it->GetValue());
        while(ss.good())
        {
            ss >> buffer;
            if(buffer == _word) return true;
        }
    }
    return false;
}
bool Search::_startingWith(Element* e, const std::string& name,
                           const std::string& phrase)
{
    std::string _phrase = phrase;
    if(_phrase.empty()) return false;
    if(name == "*" && _phrase == "*") !e->GetAttributes().empty();
    if(_phrase == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(_phrase.front() == '"' && _phrase.back() == '"' && _phrase.length() > 1)
        _phrase = _phrase.substr(1,_phrase.length()-2);
    Vector_A attributes;
    if(name == "*")
        attributes = e->GetAttributes();
    else
    {
        Attribute a = e->GetAttributeByName(name);
        if(a.GetName().empty()) return false;
        attributes.push_back(a);
    }
    for(Vector_A_it it = attributes.begin(); it != attributes.end(); ++it)
    {
        std::string value = it->GetValue();
        if(value.length() < _phrase.length()) continue;
        if(value == _phrase) return true;
        if(value.substr(0,_phrase.length()+1) == _phrase+' ' ||
                value.substr(0,_phrase.length()+1) == _phrase+'-') return true;
    }
    return false;
}
bool Search::_beginingWith(Element* e, const std::string& name,
                           const std::string& phrase)
{
    std::string _phrase = phrase;
    if(_phrase.empty()) return false;
    if(name == "*" && _phrase == "*") !e->GetAttributes().empty();
    if(_phrase == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(_phrase.front() == '"' && _phrase.back() == '"' && _phrase.length() > 1)
        _phrase = _phrase.substr(1,_phrase.length()-2);
    Vector_A attributes;
    if(name == "*")
        attributes = e->GetAttributes();
    else
    {
        Attribute a = e->GetAttributeByName(name);
        if(a.GetName().empty()) return false;
        attributes.push_back(a);
    }
    for(Vector_A_it it = attributes.begin(); it != attributes.end(); ++it)
    {
        std::string value = it->GetValue();
        if(value.length() < _phrase.length()) continue;
        if(value.substr(0,_phrase.length()) == _phrase) return true;
    }
    return false;
}
bool Search::_endingWith(Element* e, const std::string& name,
                         const std::string& phrase)
{
    std::string _phrase = phrase;
    if(_phrase.empty()) return false;
    if(name == "*" && _phrase == "*") !e->GetAttributes().empty();
    if(_phrase == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(_phrase.front() == '"' && _phrase.back() == '"' && _phrase.length() > 1)
        _phrase = _phrase.substr(1,_phrase.length()-2);
    Vector_A attributes;
    if(name == "*")
        attributes = e->GetAttributes();
    else
    {
        Attribute a = e->GetAttributeByName(name);
        if(a.GetName().empty()) return false;
        attributes.push_back(a);
    }
    for(Vector_A_it it = attributes.begin(); it != attributes.end(); ++it)
    {
        std::string value = it->GetValue();
        if(value.length() < _phrase.length()) continue;
        if(value.substr(value.length()-_phrase.length(),
                        std::string::npos) == _phrase) return true;
    }
    return false;
}
bool Search::_hasSubstr(Element* e, const std::string& name,
                        const std::string& substring)
{
    std::string _substring = substring;
    if(_substring.empty()) return false;
    if(name == "*" && _substring == "*") !e->GetAttributes().empty();
    if(_substring == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(_substring.front() == '"' && _substring.back() == '"'
       && _substring.length() > 1)
        _substring = _substring.substr(1,_substring.length()-2);
    Vector_A attributes;
    if(name == "*")
        attributes = e->GetAttributes();
    else
    {
        Attribute a = e->GetAttributeByName(name);
        if(a.GetName().empty()) return false;
        attributes.push_back(a);
    }
    for(Vector_A_it it = attributes.begin(); it != attributes.end(); ++it)
        if(it->GetValue().find(_substring) != std::string::npos) return true;
    return false;
}
}

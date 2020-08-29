#include <sstream>
#include "attribute.h"
#include "class.h"
#include "misc.h"
#include "search.h"

namespace idogaf
{
std::vector<Element> Search::Find(Element root, std::string query)
{
    std::vector<Element> result;
    std::set<Element*> resultSet;
    std::set<Element*> qResult;
    query = trim(query);
    //Count number of ',' in query
    size_t cnt = 1, pos = 0;
    while((pos = query.find(',', pos)) != std::string::npos)
    {
        cnt++;
        pos++;
    }
    for(size_t i = 0, pos1 = 0; i < cnt; i++)
    {
        size_t pos2 = query.find(',', pos1);
        std::string cmplx = trim(query.substr(pos1, pos2-pos1));
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
    for(auto it = resultSet.begin();it != resultSet.end();++it)
        result.push_back(**it);
    return result;
}

std::vector<Element*> Search::FindPtr(Element* root, std::string query)
{
    std::set<Element*> result;
    std::set<Element*> qResult;
    query = trim(query);
    //Count number of ',' in query
    size_t cnt = 0, pos = 0;
    while((pos = query.find(',', pos)) != std::string::npos)
    {
        cnt++;
        pos++;
    }
    for(size_t i = 0, pos1 = 0; i < cnt; i++)
    {
        size_t pos2 = query.find(',', pos1);
        std::string cmplx = trim(query.substr(pos1, pos2-pos1));
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
    return std::vector<Element*>(result.begin(), result.end());
}

std::vector<Element> Search::FindInVector(std::vector<Element> vec, std::string query)
{
    std::vector<Element> result, partial;
    for(auto it = vec.begin();it != vec.end();++it)
    {
        partial = Find(*it, query);
        result.insert(result.end(), partial.begin(), partial.end());
    }
    return result;
}

//Private member functions
std::set<Element*> Search::RunQuery(std::set<Element*> elements,
                                       std::string query)
{
    std::set<Element*> result;
    for(auto it = elements.begin();it != elements.end();++it)
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

bool Search::CheckElement(Element* element, std::string query)
{
    if(query.empty()) return false;
    if(element == nullptr) return false;

    switch(query.front())
    {
        case '.':
            return _ofClass(element, query.substr(1));
        case '#':
            return _hasId(element, query.substr(1));
        case '[':
        {
            if(query.back() != ']') return false;
            query = query.substr(1, query.length()-2);
            size_t pos = query.find('=');
            if(pos == std::string::npos)
                return _hasAttribute(element, trim(query));
            else
            {
                if(pos == 0 || pos == query.length()-1) return false;
                switch(query[pos-1])
                {
                    case '~':
                        return _hasWord(element, trim(query.substr(0,pos-1)),
                                        trim(query.substr(pos+1)));
                    case '|':
                        return _startingWith(element, trim(query.substr(0,pos-1)),
                                             trim(query.substr(pos+1)));
                    case '^':
                        return _beginingWith(element, trim(query.substr(0,pos-1)),
                                             trim(query.substr(pos+1)));
                    case '$':
                        return _endingWith(element, trim(query.substr(0,pos-1)),
                                           trim(query.substr(pos+1)));
                    case '*':
                    {
                        if(!trim(query.substr(0,pos-1)).empty())
                            return _hasSubstr(element, trim(query.substr(0,pos-1)),
                                              trim(query.substr(pos+1)));
                    }
                    default:
                        return _hasValue(element, trim(query.substr(0,pos)),
                                         trim(query.substr(pos+1)));
                }
            }
        }
        default:
            return element->GetName() == query;
    }
}

std::set<Element*> Search::CheckElements(std::set<Element*> elements,
                                         std::string query)
{
    std::set<Element*> result;
    for(auto it = elements.begin();it != elements.end();++it)
    {
        if(CheckElement(*it, query))
            result.insert(*it);
    }
    return result;
}

std::set<Element*> Search::ProcessSeparator(std::set<Element*> elements,
                                            char separator)
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
    return std::set<Element*>();
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
std::set<Element*> Search::_inside(std::set<Element*> elements)
{
    std::set<Element*> result;
    for(auto it = elements.begin();it != elements.end();++it)
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
                    if(e->GetParent() == nullptr) break;
                    e = e->GetParent();
                }
                if(e->GetParent() == nullptr) break;
                e = e->GetRightBrotherPtr();
            }
        }
    }
    return result;
}
std::set<Element*> Search::_child(std::set<Element*> elements)
{
    std::set<Element*> result;
    for(auto it = elements.begin();it != elements.end();++it)
    {
        auto vec = (*it)->GetChildrenPtr();
        result.insert(vec.begin(), vec.end());
    }
    return result;
}
std::set<Element*> Search::_rBrother(std::set<Element*> elements)
{
    std::set<Element*> result;
    for(auto it = elements.begin();it != elements.end();++it)
    {
        if((*it)->HasRightBrother())
            result.insert((*it)->GetRightBrotherPtr());
    }
    return result;
}
std::set<Element*> Search::_preceded(std::set<Element*> elements)
{
    std::set<Element*> result;
    for(auto it = elements.begin();it != elements.end();++it)
    {
        Element* e = *it;
        if(e->GetParent() == nullptr) continue;
        e = e->GetParent();
        for(size_t i = 0;i < e->GetChildrenCount();i++)
        {
            Element* sibling = e->GetChildPtrAt(i);
            if(sibling == *it) break;
            result.insert(sibling);
        }
    }
    return result;
}

//Single selectors
bool Search::_ofClass(Element* e, std::string name)
{
    if(name == "*") return !e->GetClass().GetValue().empty();
    return e->GetClass().Matches(name);
}
bool Search::_hasId(Element* e, std::string name)
{
    if(name == "*") return !e->GetId().GetValue().empty();
    return e->GetId().GetValue() == name;
}
bool Search::_hasAttribute(Element* e, std::string name)
{
    if(name == "*") return !e->GetAttributes().empty();
    return !e->GetAttributeByName(name).GetName().empty();
}
bool Search::_hasValue(Element* e, std::string name, std::string value)
{
    if(value.empty()) return false;
    if(name == "*" && value == "*") !e->GetAttributes().empty();
    if(value == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(value.front() == '"' && value.back() == '"' && value.length() > 1)
        value = value.substr(1,value.length()-2);
    if(name == "*")
    {
        std::vector<Attribute> attributes = e->GetAttributes();
        for(auto it = attributes.begin();it != attributes.end();++it)
        {
            if(it->GetValue() == value) return true;
        }
        return false;
    }
    return e->GetAttributeByName(name).GetValue() == value;
}
bool Search::_hasWord(Element* e, std::string name, std::string word)
{
    if(word.empty()) return false;
    if(name == "*" && word == "*") !e->GetAttributes().empty();
    if(word == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(word.front() == '"' && word.back() == '"' && word.length() > 1)
        word = word.substr(1,word.length()-2);
    std::vector<Attribute> attributes;
    if(name == "*")
        attributes = e->GetAttributes();
    else
    {
        Attribute a = e->GetAttributeByName(name);
        if(a.GetName().empty()) return false;
        attributes.push_back(a);
    }
    std::string buffer;
    for(auto it = attributes.begin();it != attributes.end();++it)
    {
        std::stringstream ss(it->GetValue());
        while(ss.good())
        {
            ss >> buffer;
            if(buffer == word) return true;
        }
    }
    return false;
}
bool Search::_startingWith(Element* e, std::string name, std::string phrase)
{
    if(phrase.empty()) return false;
    if(name == "*" && phrase == "*") !e->GetAttributes().empty();
    if(phrase == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(phrase.front() == '"' && phrase.back() == '"' && phrase.length() > 1)
        phrase = phrase.substr(1,phrase.length()-2);
    std::vector<Attribute> attributes;
    if(name == "*")
        attributes = e->GetAttributes();
    else
    {
        Attribute a = e->GetAttributeByName(name);
        if(a.GetName().empty()) return false;
        attributes.push_back(a);
    }
    for(auto it = attributes.begin();it != attributes.end();++it)
    {
        std::string value = it->GetValue();
        if(value.length() < phrase.length()) continue;
        if(value == phrase) return true;
        if(value.substr(0,phrase.length()+1) == phrase+' ' ||
            value.substr(0,phrase.length()+1) == phrase+'-') return true;
    }
    return false;
}
bool Search::_beginingWith(Element* e, std::string name, std::string phrase)
{
    if(phrase.empty()) return false;
    if(name == "*" && phrase == "*") !e->GetAttributes().empty();
    if(phrase == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(phrase.front() == '"' && phrase.back() == '"' && phrase.length() > 1)
        phrase = phrase.substr(1,phrase.length()-2);
    std::vector<Attribute> attributes;
    if(name == "*")
        attributes = e->GetAttributes();
    else
    {
        Attribute a = e->GetAttributeByName(name);
        if(a.GetName().empty()) return false;
        attributes.push_back(a);
    }
    for(auto it = attributes.begin();it != attributes.end();++it)
    {
        std::string value = it->GetValue();
        if(value.length() < phrase.length()) continue;
        if(value.substr(0,phrase.length()) == phrase) return true;
    }
    return false;
}
bool Search::_endingWith(Element* e, std::string name, std::string phrase)
{
    if(phrase.empty()) return false;
    if(name == "*" && phrase == "*") !e->GetAttributes().empty();
    if(phrase == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(phrase.front() == '"' && phrase.back() == '"' && phrase.length() > 1)
        phrase = phrase.substr(1,phrase.length()-2);
    std::vector<Attribute> attributes;
    if(name == "*")
        attributes = e->GetAttributes();
    else
    {
        Attribute a = e->GetAttributeByName(name);
        if(a.GetName().empty()) return false;
        attributes.push_back(a);
    }
    for(auto it = attributes.begin();it != attributes.end();++it)
    {
        std::string value = it->GetValue();
        if(value.length() < phrase.length()) continue;
        if(value.substr(value.length()-phrase.length(),
                        std::string::npos) == phrase) return true;
    }
    return false;
}
bool Search::_hasSubstr(Element* e, std::string name, std::string substring)
{
    if(substring.empty()) return false;
    if(name == "*" && substring == "*") !e->GetAttributes().empty();
    if(substring == "*") return !e->GetAttributeByName(name).GetName().empty();
    if(substring.front() == '"' && substring.back() == '"' && substring.length() > 1)
        substring = substring.substr(1,substring.length()-2);
    std::vector<Attribute> attributes;
    if(name == "*")
        attributes = e->GetAttributes();
    else
    {
        Attribute a = e->GetAttributeByName(name);
        if(a.GetName().empty()) return false;
        attributes.push_back(a);
    }
    for(auto it = attributes.begin();it != attributes.end();++it)
        if(it->GetValue().find(substring) != std::string::npos) return true;
    return false;
}
}

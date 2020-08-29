/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef SEARCH_H
#define SEARCH_H

#include <set>
#include <string>
#include <vector>
#include "attribute.h"
#include "element.h"

namespace idogaf
{
class Search
{
    public:
        /** Find elements in a tree

            This function uses CSS selectors to search for elements
            in a given tree. Pseudo-classes and pseudo-elements are not
            supported right now. If a query matches an element twice
            (i.e. "div, .xxx" matches <div class="xxx">) then it will
            be included only once in a result vector (it won't be duplicated).

            @param root Root element of the tree to search in.
            @param query CSS selector query.
            @return Vector containg every element matching given query.
        */
        static std::vector<Element> Find(Element root, std::string query);
        /** Find elements in a tree

            This function uses CSS selectors to search for elements
            in a given tree. Pseudo-classes and pseudo-elements are not
            supported right now. If a query matches an element twice
            (i.e. "div, .xxx" matches <div class="xxx">) then it will
            be included only once in a result vector (it won't be duplicated).
            Warning: Due to operating on pointers, if during this function
            execution the tree is modified (possibly resulting in the
            invalidation of some pointers), the result of the function is
            undefined and possibility of a segmentation fault exists.
            Warning: Currently this will also search in root elements right
            siblings and it's ancestors right siblings and their children.
            Use Search::Find() for stable results.

            @param root Pointer to the root element of the tree to search in.
            @param query CSS selector query.
            @return Vector containg pointers to the elements matching given query.
        */
        static std::vector<Element*> FindPtr(Element* root, std::string query);
        /** Find elements in a vector of trees

            This function uses CSS selectors to search for elements
            in a given trees. Pseudo-classes and pseudo-elements are not
            supported right now. If a query matches an element twice
            (i.e. "div, .xxx" matches <div class="xxx">) then it will
            be included only once in a result vector (it won't be duplicated).
            If applies only to the single tree (single element in a given
            vector) since if the copy of an element is in any other tree it's
            considered a diffrent element.

            @param vec Vector containing root elements of the trees to search in.
            @return query CSS selector query.
        */
        static std::vector<Element> FindInVector(std::vector<Element> vec,
                                                 std::string query);

    protected:

    private:
        /** Run single query */
        static std::set<Element*> RunQuery(std::set<Element*> elements,
                                           std::string query);
        /** Check element for a single query

            @param element Pointer to the element to check.
            @param query Single query to check.
            @return True if the element matches the query, false otherwise.
        */
        static bool CheckElement(Element* element, std::string query);
        /** Check multiple elements for a single query

            @param elements Set of pointers to the Element objects to check.
            @param query Single query to check.
            @return Vector of pointers to the elements matching the query.
        */
        static std::set<Element*> CheckElements(std::set<Element*> elements,
                                                std::string query);

        /** Process separator

            Processes elements against one of the separators:
            ' ', '>', '+', '~'. I.e. if separator is '>' the function returns
            a set containing direct children of the elements in a given set.

            @param elements Set of elements matching left side of the separator.
            @param separator Separator character.
            @return Set of elements to check against the right side of the separator.
        */
        static std::set<Element*> ProcessSeparator(std::set<Element*> elements,
                                                   char separator);
        /** Find separator sign

            Finds first of ' ', '>', '+', '~', '.', '[', '#' characters
            and returns it's positions in a given string. If the function fails
            to find any those characters, then it returns std::string::npos.

            @param query Query to search for a separator in.
            @return Position of the first found separator or std::string::npos.
        */
        static size_t FindSeparator(const std::string& query);

        //Separators
        static std::set<Element*> _inside(std::set<Element*> elements);
        static std::set<Element*> _child(std::set<Element*> elements);
        static std::set<Element*> _rBrother(std::set<Element*> elements);
        static std::set<Element*> _preceded(std::set<Element*> elements);

        //Single selectors
        static bool _ofClass(Element* e, std::string name);
        static bool _hasId(Element* e, std::string name);
        static bool _hasAttribute(Element* e, std::string name);
        static bool _hasValue(Element* e, std::string name, std::string value);
        static bool _hasWord(Element* e, std::string name, std::string word);
        static bool _startingWith(Element* e, std::string name, std::string phrase);
        static bool _beginingWith(Element* e, std::string name, std::string phrase);
        static bool _endingWith(Element* e, std::string name, std::string phrase);
        static bool _hasSubstr(Element* e, std::string name, std::string substring);
};
}

#endif // SEARCH_H

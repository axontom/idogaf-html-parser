/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <vector>
#include "element.h"

namespace idogaf
{
/** Class for handling memory mangement of Element class objects .
    Dont' use this class directly, you should use static class Manager instead.
*/
class MemoryManager
{
    public:
        /** Default constructor */
        MemoryManager();
        /** Default destructor */
        ~MemoryManager();

        /** Associate an Element object
            @param element Pointer to the element to associate.
        */
        void Add(Element* element);
        /** Delete every associated Element object */
        void Cleanup();

    protected:

    private:
        std::vector<Element*> list_;

};
}
#endif // MEMORYMANAGER_H

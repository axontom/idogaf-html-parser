/** Copyright (c) 2020 Tomasz Rusinowicz
*/

#ifndef MANAGER_H
#define MANAGER_H

#include "element.h"
#include "memorymanager.h"

namespace idogaf
{
/** Static class for handling MemoryManager */
class Manager
{
    public:
        /** Associate an Element object with memory manager
            @param element Pointer to the element to associate.
        */
        static void Add(Element* element);
        /** Delete every Element object associated with the memory manager */
        static void Cleanup()

    protected:

    private:
        static MemoryManager mm_;

};
}
#endif // MANAGER_H

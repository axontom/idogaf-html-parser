#include "memorymanager.h"

namespace idogaf
{
MemoryManager::MemoryManager()
{
    //ctor
}

MemoryManager::Add(Element* element)
{
    list_.push_back(element);
}

MemoryManager::Cleanup()
{
    for(size_t i = 0; i < list_.size();i++)
        delete list_[i];
    list_.erase();
}

MemoryManager::~MemoryManager()
{
    //dtor
    if(!list_.empty())
        Cleanup();
}
}

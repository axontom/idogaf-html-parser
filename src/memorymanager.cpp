#include "memorymanager.h"

namespace idogaf
{
MemoryManager::MemoryManager()
{
    //ctor
}

void MemoryManager::Add(Element* element)
{
    list_.push_back(element);
}

void MemoryManager::Cleanup()
{
    for(size_t i = 0; i < list_.size();i++)
        delete list_[i];
    list_.clear();
}

MemoryManager::~MemoryManager()
{
    //dtor
    if(!list_.empty())
        Cleanup();
}
}

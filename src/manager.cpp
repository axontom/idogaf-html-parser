#include "manager.h"

namespace idogaf
{
    MemoryManager Manager::mm_ = MemoryManager();
    void Manager::Add(Element* element) { mm_.Add(element); }
    void Manager::Cleanup() { mm_.Cleanup(); }
}

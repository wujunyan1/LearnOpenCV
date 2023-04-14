#include "Ref.h"
#include "AutoreleasePool.h"

#if REF_LEAK_DETECTION
#include <algorithm>    // std::find
#include <thread>
#include <mutex>
#include <vector>
#endif

namespace Core
{
    unsigned long long Ref::_id = 0;

    Ref::Ref()
        : _referenceCount(1) // when the Ref is created, the reference count of it is 1
    {
        id = _id++;
    }

    Ref::~Ref()
    {
    }

    void Ref::retain()
    {
        ++_referenceCount;
    }

    void Ref::release()
    {
        --_referenceCount;

        if (_referenceCount == 0)
        {
            delete this;
        }
    }

    Ref* Ref::autorelease()
    {
        PoolManager::getInstance()->getCurrentPool()->addObject(this);
        return this;
    }

    unsigned int Ref::getReferenceCount() const
    {
        return _referenceCount;
    }

}

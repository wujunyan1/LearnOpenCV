#include "EventTouch.h"
// #include "Touch.h"

namespace Core
{
    EventTouch::EventTouch()
        : Event(Type::TOUCH)
    {
        _touches.reserve(MAX_TOUCHES);
    }
}


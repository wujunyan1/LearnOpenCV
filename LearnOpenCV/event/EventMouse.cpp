#include "EventMouse.h"

namespace Core
{

    EventMouse::EventMouse(MouseEventType mouseEventCode)
    : Event(Type::MOUSE)
    , _mouseEventType(mouseEventCode)
    , _mouseButton(MouseButton::BUTTON_UNSET)
    , _x(0.0f)
    , _y(0.0f)
    , _scrollX(0.0f)
    , _scrollY(0.0f)
    , _startPointCaptured(false)
    {
    };

    // returns the current touch location in screen coordinates
    Math::Vector2 EventMouse::getLocationInView() const
    { 
        return _point; 
    }

    // returns the previous touch location in screen coordinates
    Math::Vector2 EventMouse::getPreviousLocationInView() const
    { 
        return _prevPoint; 
    }

    // returns the start touch location in screen coordinates
    Math::Vector2 EventMouse::getStartLocationInView() const
    { 
        return _startPoint; 
    }

    // returns the current touch location in OpenGL coordinates
    Math::Vector2 EventMouse::getLocation() const
    { 
        return {0, 0};
    }

    // returns the previous touch location in OpenGL coordinates
    Math::Vector2 EventMouse::getPreviousLocation() const
    { 
        return { 0, 0 };
    }

    // returns the start touch location in OpenGL coordinates
    Math::Vector2 EventMouse::getStartLocation() const
    { 
        return { 0, 0 };
    }

    // returns the delta position between the current location and the previous location in OpenGL coordinates
    Math::Vector2 EventMouse::getDelta() const
    {     
        return getLocation() - getPreviousLocation();
    }
}

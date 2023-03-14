#include "EventListenerMouse.h"

namespace Core
{
    const std::string EventListenerMouse::LISTENER_ID = "__gl_mouse";

    bool EventListenerMouse::checkAvailable()
    {
        return true;
    }

    EventListenerMouse* EventListenerMouse::create()
    {
        auto ret = new (std::nothrow) EventListenerMouse();
        if (ret && ret->init())
        {
            ret->autorelease();
        }
        else
        {
            SAFE_DELETE(ret);
        }
        return ret;
    }

    EventListenerMouse* EventListenerMouse::clone()
    {
        auto ret = new (std::nothrow) EventListenerMouse();
        if (ret && ret->init())
        {
            ret->autorelease();
            ret->onMouseUp = onMouseUp;
            ret->onMouseDown = onMouseDown;
            ret->onMouseMove = onMouseMove;
            ret->onMouseScroll = onMouseScroll;
        }
        else
        {
            SAFE_DELETE(ret);
        }
        return ret;
    }

    EventListenerMouse::EventListenerMouse()
    : onMouseDown(nullptr)
    , onMouseUp(nullptr)
    , onMouseMove(nullptr)
    , onMouseScroll(nullptr)
    {
    }

    bool EventListenerMouse::init()
    {
        auto listener = [this](Event* event){
            auto mouseEvent = static_cast<EventMouse*>(event);
            switch (mouseEvent->_mouseEventType)
            {
                case EventMouse::MouseEventType::MOUSE_DOWN:
                    if(onMouseDown != nullptr)
                        onMouseDown(mouseEvent);
                    break;
                case EventMouse::MouseEventType::MOUSE_UP:
                    if(onMouseUp != nullptr)
                        onMouseUp(mouseEvent);
                    break;
                case EventMouse::MouseEventType::MOUSE_MOVE:
                    if(onMouseMove != nullptr)
                        onMouseMove(mouseEvent);
                    break;
                case EventMouse::MouseEventType::MOUSE_SCROLL:
                    if(onMouseScroll != nullptr)
                        onMouseScroll(mouseEvent);
                    break;
                default:
                    break;
            }
        };

        if (EventListener::init(Type::MOUSE, LISTENER_ID, listener))
        {
            return true;
        }

        return false;
    }

}

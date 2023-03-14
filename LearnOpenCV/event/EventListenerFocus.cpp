#include "EventListenerFocus.h"
#include "EventFocus.h"

namespace Core
{
    const std::string EventListenerFocus::LISTENER_ID = "__cc_focus_event";


    EventListenerFocus::EventListenerFocus()
    :onFocusChanged(nullptr)
    {
    
    }

    EventListenerFocus::~EventListenerFocus()
    {
        printf("In the destructor of EventListenerFocus, %p", this);
    }

    EventListenerFocus* EventListenerFocus::create()
    {
        EventListenerFocus* ret = new (std::nothrow) EventListenerFocus;
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        SAFE_DELETE(ret);
        return nullptr;
    }

    EventListenerFocus* EventListenerFocus::clone()
    {
        EventListenerFocus* ret = new (std::nothrow) EventListenerFocus;
        if (ret && ret->init()) {
            ret->autorelease();
        
            ret->onFocusChanged = onFocusChanged;
        }
        else
        {
            SAFE_DELETE(ret);
        }
        return ret;
    }

    bool EventListenerFocus::init()
    {
        auto listener = [this](Event* event){
            auto focusEvent = static_cast<EventFocus*>(event);
            onFocusChanged(focusEvent->_widgetLoseFocus, focusEvent->_widgetGetFocus);
        };
        if (EventListener::init(Type::FOCUS, LISTENER_ID, listener)) {
            return true;
        }
        return false;
    }

    bool EventListenerFocus::checkAvailable()
    {
        if (onFocusChanged == nullptr)
        {
            return false;
        }
    
        return true;
    }
}


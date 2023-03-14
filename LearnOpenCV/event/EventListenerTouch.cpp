#include "EventListenerTouch.h"
#include "EventDispatcher.h"
#include "EventTouch.h"
//#include "base/CCTouch.h"

#include <algorithm>

namespace Core
{

    const std::string EventListenerTouchOneByOne::LISTENER_ID = "__cc_touch_one_by_one";

    EventListenerTouchOneByOne::EventListenerTouchOneByOne()
    : onTouchBegan(nullptr)
    , onTouchMoved(nullptr)
    , onTouchEnded(nullptr)
    , onTouchCancelled(nullptr)
    , _needSwallow(false)
    {
    }

    EventListenerTouchOneByOne::~EventListenerTouchOneByOne()
    {
        printf("In the destructor of EventListenerTouchOneByOne, %p", this);
    }

    bool EventListenerTouchOneByOne::init()
    {
        if (EventListener::init(Type::TOUCH_ONE_BY_ONE, LISTENER_ID, nullptr))
        {
            return true;
        }
    
        return false;
    }

    void EventListenerTouchOneByOne::setSwallowTouches(bool needSwallow)
    {
        _needSwallow = needSwallow;
    }

    bool EventListenerTouchOneByOne::isSwallowTouches()
    {
        return _needSwallow;
    }

    EventListenerTouchOneByOne* EventListenerTouchOneByOne::create()
    {
        auto ret = new (std::nothrow) EventListenerTouchOneByOne();
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

    bool EventListenerTouchOneByOne::checkAvailable()
    {
        // EventDispatcher will use the return value of 'onTouchBegan' to determine whether to pass following 'move', 'end'
        // message to 'EventListenerTouchOneByOne' or not. So 'onTouchBegan' needs to be set.
        if (onTouchBegan == nullptr)
        {
            return false;
        }
    
        return true;
    }

    EventListenerTouchOneByOne* EventListenerTouchOneByOne::clone()
    {
        auto ret = new (std::nothrow) EventListenerTouchOneByOne();
        if (ret && ret->init())
        {
            ret->autorelease();
        
            ret->onTouchBegan = onTouchBegan;
            ret->onTouchMoved = onTouchMoved;
            ret->onTouchEnded = onTouchEnded;
            ret->onTouchCancelled = onTouchCancelled;
        
            ret->_claimedTouches = _claimedTouches;
            ret->_needSwallow = _needSwallow;
        }
        else
        {
            SAFE_DELETE(ret);
        }
        return ret;
    }

    const std::string EventListenerTouchAllAtOnce::LISTENER_ID = "__cc_touch_all_at_once";

    EventListenerTouchAllAtOnce::EventListenerTouchAllAtOnce()
    : onTouchesBegan(nullptr)
    , onTouchesMoved(nullptr)
    , onTouchesEnded(nullptr)
    , onTouchesCancelled(nullptr)
    {
    }

    EventListenerTouchAllAtOnce::~EventListenerTouchAllAtOnce()
    {
        printf("In the destructor of EventListenerTouchAllAtOnce, %p", this);
    }

    bool EventListenerTouchAllAtOnce::init()
    {
        if (EventListener::init(Type::TOUCH_ALL_AT_ONCE, LISTENER_ID, nullptr))
        {
            return true;
        }
    
        return false;
    }

    EventListenerTouchAllAtOnce* EventListenerTouchAllAtOnce::create()
    {
        auto ret = new (std::nothrow) EventListenerTouchAllAtOnce();
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

    bool EventListenerTouchAllAtOnce::checkAvailable()
    {
        if (onTouchesBegan == nullptr && onTouchesMoved == nullptr
            && onTouchesEnded == nullptr && onTouchesCancelled == nullptr)
        {
            return false;
        }
    
        return true;
    }

    EventListenerTouchAllAtOnce* EventListenerTouchAllAtOnce::clone()
    {
        auto ret = new (std::nothrow) EventListenerTouchAllAtOnce();
        if (ret && ret->init())
        {
            ret->autorelease();
        
            ret->onTouchesBegan = onTouchesBegan;
            ret->onTouchesMoved = onTouchesMoved;
            ret->onTouchesEnded = onTouchesEnded;
            ret->onTouchesCancelled = onTouchesCancelled;
        }
        else
        {
            SAFE_DELETE(ret);
        }
        return ret;
    }

 }

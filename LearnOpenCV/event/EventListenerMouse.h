#pragma once
#include "EventListener.h"
#include "EventMouse.h"

namespace Core
{

    class Event;

    /** @class EventListenerMouse
     * @brief Mouse event listener.
     * @js cc._EventListenerMouse
     */
    class EventListenerMouse : public EventListener
    {
    public:
        static const std::string LISTENER_ID;
    
        /** Create a mouse event listener.
         *
         * @return An autoreleased EventListenerMouse object.
         */
        static EventListenerMouse* create();

        /// Overrides
        virtual EventListenerMouse* clone() override;
        virtual bool checkAvailable() override;

        std::function<void(EventMouse* event)> onMouseDown;
        std::function<void(EventMouse* event)> onMouseUp;
        std::function<void(EventMouse* event)> onMouseMove;
        std::function<void(EventMouse* event)> onMouseScroll;

        EventListenerMouse();
        bool init();
    };
}
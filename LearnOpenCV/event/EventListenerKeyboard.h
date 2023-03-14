#pragma once
#include "EventListener.h"
#include "EventKeyboard.h"

/**
 * @addtogroup base
 * @{
 */

namespace Core
{
    class Event;

    /** @class EventListenerKeyboard
     * @brief Keyboard event listener.
     * @js cc._EventListenerKeyboard
     */
    class EventListenerKeyboard : public EventListener
    {
    public:
        static const std::string LISTENER_ID;

        /** Create a keyboard event listener.
         *
         * @return An autoreleased EventListenerKeyboard object.
         */
        static EventListenerKeyboard* create();

        /// Overrides
        virtual EventListenerKeyboard* clone() override;
        virtual bool checkAvailable() override;

        std::function<void(Core::EventKeyboard::KeyCode, Core::Event*)> onKeyPressed;
        std::function<void(Core::EventKeyboard::KeyCode, Core::Event*)> onKeyReleased;
        EventListenerKeyboard();
        bool init();
    };

}

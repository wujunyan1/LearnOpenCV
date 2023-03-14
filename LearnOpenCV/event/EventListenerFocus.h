#pragma once
#include "EventListener.h"

/**
 * @addtogroup base
 * @{
 */

namespace Core
{

    namespace ui {
        class Widget;
    }

    /** @class EventListenerFocus
     * @brief Focus event listener.
     */
    class EventListenerFocus : public EventListener
    {
    public:
        static const std::string LISTENER_ID;
    
        /** Create a focus event listener.
         *
         * @return An autoreleased EventListenerFocus object.
         */
        static EventListenerFocus* create();
    
        /** Destructor.
         * @js NA
         */
        virtual ~EventListenerFocus();
    
        /// Overrides
        virtual EventListenerFocus* clone() override;
        virtual bool checkAvailable() override;
        //
    
    public:
        std::function<void(ui::Widget*, ui::Widget*)> onFocusChanged;
    
        EventListenerFocus();
        bool init();
    
        friend class EventDispatcher;
    };
}
#pragma onde
#include "Event.h"

namespace ui {
    class Widget;
}

namespace Core
{
    /** @class EventFocus
 * @brief Focus event.
 */
    class EventFocus : public Event
    {
    public:
        /** Constructor.
         *
         * @param widgetLoseFocus The widget which lose focus.
         * @param widgetGetFocus The widget which get focus.
         * @js ctor
         */
        EventFocus(ui::Widget* widgetLoseFocus, ui::Widget* widgetGetFocus);

    private:
        ui::Widget* _widgetGetFocus;
        ui::Widget* _widgetLoseFocus;

        friend class EventListenerFocus;
    };
}
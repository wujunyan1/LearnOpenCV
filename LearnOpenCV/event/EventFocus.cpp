#include "EventFocus.h"

using namespace Core;

EventFocus::EventFocus(ui::Widget *widgetLoseFocus, ui::Widget* widgetGetFocus)
:Event(Type::FOCUS),
_widgetGetFocus(widgetGetFocus),
_widgetLoseFocus(widgetLoseFocus)
{
    
}
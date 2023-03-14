#include "EventCustom.h"
#include "Event.h"

using namespace Core;

EventCustom::EventCustom(const std::string& eventName)
: Event(Type::CUSTOM)
, _userData(nullptr)
, _eventName(eventName)
{
}
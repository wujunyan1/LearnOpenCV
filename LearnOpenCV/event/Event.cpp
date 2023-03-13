#include "Event.h"

using namespace Core;

Core::EventManager::EventManager()
{
	events = std::map<std::string, Event>();
}

Core::EventManager::~EventManager()
{
}

Event::unsubscribe Core::EventManager::registerEvent(std::string& name, Event::Callback callback)
{
	auto it = events.find(name);
	Event eventObj = it->second;
	if (it == events.end())
	{
		eventObj = Event(name);
	}

	return eventObj.pushCallback(callback);
}

bool Core::EventManager::emit(std::string& name, ...)
{


	return false;
}

#pragma once
#include <functional>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <map>
#include <list>

using namespace Core;
namespace Core
{
	class Event
	{
		friend class EventManager;
	public:
		using Callback = std::function<bool()>;

		using unsubscribe = std::function<bool()>;

		Event(std::string& name) :m_name(name) {};

	private:

		template<class ...Args>
		unsubscribe pushCallback(Callback callback)
		{
			subscribers.push_back(callback);
			std::list<Callback>::iterator iter = --subscribers.end();
			
			return [=]()-> bool {
				subscribers.erase(iter);
				return true;
			};
		};


		std::list<Callback> subscribers;
		std::string m_name;
	};

	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		Event::unsubscribe registerEvent(std::string& name, Event::Callback callback);
		bool emit(std::string& name, ...);

	private:
		std::map<std::string, Event> events;
	};
}

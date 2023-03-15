#pragma once
#include "Core.h"
#include "Ref.h"
#include <map>

#include "../event/Event.h"
#include "../event/EventDispatcher.h"
#include "../event/EventCustom.h"

namespace Core
{
	static class GlobalDictionary
	{
	public:
		static void initGame();
		static void destroyGame();

		static EventDispatcher* getDispatcher() { return dispatcher; };
	private:
		static EventDispatcher* dispatcher;
	};
}

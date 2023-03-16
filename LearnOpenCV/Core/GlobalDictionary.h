#pragma once
#include "Core.h"
#include "Ref.h"
#include <map>

#include "../event/Event.h"
#include "../event/EventDispatcher.h"
#include "../event/EventCustom.h"

#include "../math/Vector2T.h"
namespace Core
{
	static class GlobalDictionary
	{
	public:
		static void initGame();
		static void destroyGame();

		static Math::Vector2T<int> getRealWindowSize() { return m_realWindowSize; };
		static void setRealWindowSize(Math::Vector2T<int> size);

		static EventDispatcher* getDispatcher() { return dispatcher; };
	private:
		static EventDispatcher* dispatcher;

		static Math::Vector2T<int> m_realWindowSize;
	};
}

#include "GlobalDictionary.h"

namespace Core
{
	EventDispatcher* GlobalDictionary::dispatcher = new EventDispatcher();
	Math::Vector2T<int> GlobalDictionary::m_realWindowSize = { 1280, 720 };

	void GlobalDictionary::initGame()
	{
		dispatcher->setEnabled(true);
	}

	void GlobalDictionary::destroyGame()
	{
		/*dispatcher->removeAllEventListeners();
		dispatcher->setEnabled(false);*/
		SAFE_DELETE(dispatcher);
	}
	void GlobalDictionary::setRealWindowSize(Math::Vector2T<int> size)
	{
		m_realWindowSize = size;
		dispatcher->dispatchCustomEvent("winSizeChangeEvent", &size);
	}
}
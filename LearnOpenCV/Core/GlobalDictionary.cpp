#include "GlobalDictionary.h"

namespace Core
{
	EventDispatcher* GlobalDictionary::dispatcher = new EventDispatcher();
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
}
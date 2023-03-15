#include "UICanvas.h"
#include "../Core/GlobalDictionary.h"

using namespace Core;

namespace UI
{
	UICanvas::UICanvas() : Transform()
	{
		GlobalDictionary::getDispatcher()->addCustomEventListener("winSizeChangeEvent", [this](EventCustom* _event) {
			Math::Vector2T<int>* size = (Math::Vector2T<int>*)_event->getUserData();
			
		});
	}
}
#include "UICanvas.h"
#include "../Core/GlobalDictionary.h"
#include "UITransform.h"

using namespace Core;

namespace UI
{
	UICanvas::UICanvas() : Component()
	{
		GlobalDictionary::getDispatcher()->addCustomEventListener("winSizeChangeEvent", [this](EventCustom* _event) {
			Math::Vector2T<int>* size = (Math::Vector2T<int>*)_event->getUserData();
			updateUITransform({ size->x, size->y });
		});
	}

	void UICanvas::Render()
	{

	}

	void UICanvas::updateUITransform(Vector2 size)
	{
		UITransform* transform = getObject()->GetComponent<UITransform>();
		transform->m_realSize = size;
	}
}
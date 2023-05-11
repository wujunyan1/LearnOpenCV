#include "UICanvas.h"
#include "../Core/GlobalDictionary.h"
#include "UITransform.h"

using namespace Core;

namespace UI
{
	UICanvas::UICanvas() : GameComponent()
	{
		GlobalDictionary::getDispatcher()->addCustomEventListener("winSizeChangeEvent", [this](EventCustom* _event) {
			Math::Vector2T<int>* size = (Math::Vector2T<int>*)_event->getUserData();
			updateUITransform({ (float)size->x, (float)size->y });
		});
	}

	void UICanvas::Bind()
	{
		UITransform* transform = getObject()->GetComponent<UITransform>();
		Math::Vector2T<int> windowSize = GlobalDictionary::getRealWindowSize();
		//transform->m_realSize = { (float)windowSize.x, (float)windowSize.y };
		transform->SetPosition({ { 0, -0.5f * windowSize.x }, { 0, -0.5f * windowSize.y } });
		transform->SetPivot({ 0, 0 });
		transform->SetSize({ {0, 1.0f * windowSize.x}, {0, 1.0f * windowSize.y} });
		transform->UpdateLocalMat4();
	}

	void UICanvas::Render()
	{
		Render::AddUICanvas(this);
	}

	void UICanvas::updateUITransform(Vector2 size)
	{
		UITransform* transform = getObject()->GetComponent<UITransform>();
		transform->m_realSize = size;
	}
}
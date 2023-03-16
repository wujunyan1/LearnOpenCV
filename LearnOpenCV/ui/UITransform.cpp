#include "UITransform.h"
#include "../Core/GlobalDictionary.h"

using namespace Core;

void UI::UITransform::UpdateRealPosition()
{
	Math::Vector2T<int> windowSize = GlobalDictionary::getRealWindowSize();
	Vector2 parentSize = { windowSize.x, windowSize.y };

	Object* parent = dynamic_cast<Object*>(getObject()->GetParent());
	if (parent) {
		UITransform* parentTransform = parent->GetComponent<UITransform>();
		if (parentTransform)
		{
			parentSize = parentTransform->m_realSize;
		}
	}

	float width = parentSize.x * rect_size.x.x + rect_size.x.y;
	float height = parentSize.y * rect_size.y.x + rect_size.y.y;
	m_realSize.x = width;
	m_realSize.y = height;

	float x = parentSize.x * rect_position.x.x + rect_position.x.y;
	float y = parentSize.y * rect_position.y.x + rect_position.y.y;
	m_realPosition.x = x;
	m_realPosition.y = y;
}

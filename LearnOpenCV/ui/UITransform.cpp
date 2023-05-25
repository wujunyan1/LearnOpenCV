#include "UITransform.h"
#include "../Core/GlobalDictionary.h"
#include "UICanvas.h"

using namespace Core;

UI::UITransform::UITransform()
{
	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_rotate = Vector3(0.0f, 0.0f, 0.0f);

	localToWorldMat4 = Mat4(1.0f);
	localMat4 = Mat4(1.0f);
	rotateMat = Mat4(1.0f);
	worldToLocalMat4 = Mat4(1.0f);


	matChanged = true;
}

void UI::UITransform::Render()
{
}

void UI::UITransform::UpdateRealPosition()
{
	Math::Vector2T<int> windowSize = GlobalDictionary::getRealWindowSize();
	Vector2 parentSize = { (float)windowSize.x, (float)windowSize.y };

	Object* parent = dynamic_cast<Object*>(getGameObject()->GetParent());
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

	printf("m_realSize %f %f \n", m_realSize.x, m_realSize.y);
	printf("m_realPosition %f %f \n", m_realPosition.x, m_realPosition.y);

}

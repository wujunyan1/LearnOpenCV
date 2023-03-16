#pragma once
#include "../Core/Core.h"
#include "../Core/Component.h"
#include "../Core/Object.h"
#include "../Core/Transform.h"
#include "../math/UVector2.h"
#include <vector>

using namespace Core;
using namespace Math;
namespace UI 
{
	class UITransform : public Component
	{
	public:

		UITransform() : Component()
		{

		}

		UVector2 GetPosition() {
			return rect_position;
		}

		void SetPosition(UVector2 v) {
			rect_position = v;
			matChanged = true;
		}

		void SetScale(Vector3 v) {
			m_scale = v;
			matChanged = true;
		}

		// https://zhuanlan.zhihu.com/p/45404840
		// https://baike.baidu.com/item/%E6%AC%A7%E6%8B%89%E8%A7%92/1626212
		void SetRotate(Vector3 rotate) {
			rotateMat = Mat4::rotate(rotate.y, Vector3(0.0f, 1.0f, 0.0f));
			rotateMat = Mat4::rotate(rotate.x, Vector3(1.0f, 0.0f, 0.0f)) * rotateMat;
			rotateMat = Mat4::rotate(rotate.z, Vector3(0.0f, 0.0f, 1.0f)) * rotateMat;

			this->m_rotate = rotate;
			matChanged = true;
		}

		Vector3 GetRotate() {
			return m_rotate;
		}

		Mat4& GetLocalToWorldMat4() {
			if (matChanged) {
				UpdateLocalMat4();
			}
			return localToWorldMat4;
		}

		Mat4& GetWorldToLocalMat4() {
			if (matChanged) {
				UpdateLocalMat4();
			}
			return worldToLocalMat4;
		}

		Mat4& GetLocalMat4() {
			if (matChanged) {
				UpdateLocalMat4();
			}
			return localMat4;
		}


	private:

		void UpdateRealPosition();

		void UpdateLocalMat4() {
			// 缩放 锚点平移 旋转 平移
			localMat4 = Mat4::scale(Vector3(m_scale.x, m_scale.y, 1));
			localMat4 = Mat4::translate(m_realSize * pivot) * localMat4;
			localMat4 = rotateMat * localMat4;
			localMat4 = Mat4::translate(m_realPosition) * localMat4;

			updateLocalToWorldMat4();
			updateWorldToLocalMat4();

			matChanged = false;
		}

		void updateLocalToWorldMat4()
		{
			localToWorldMat4 = localMat4;

			Object* parent = dynamic_cast<Object*>(getObject()->GetParent());
			if (parent) {
				UITransform* parentTransform = parent->GetComponent<UITransform>();
				if (parentTransform)
				{
					localToWorldMat4 = parentTransform->localToWorldMat4 * localMat4;
				}
			}

			std::vector<TreeNode*>* children = getObject()->getChildren();
			if (children) {
				for (auto i : *children)
				{
					Object* obj = dynamic_cast<Object*>(i);
					if (obj) {
						UITransform* objTransform = obj->GetComponent<UITransform>();
						if (objTransform)
						{
							objTransform->updateLocalToWorldMat4();
						}
					}
				}
			}
		}

		void updateWorldToLocalMat4()
		{
			worldToLocalMat4 = rotateMat.clone().transpose();
			worldToLocalMat4 = worldToLocalMat4 * Mat4::translate(-m_realPosition);
			worldToLocalMat4 = Mat4::scale(Vector3(1.0f / m_scale.x, 1.0f / m_scale.y, 1.0f)) * worldToLocalMat4;

			Object* parent = dynamic_cast<Object*>(getObject()->GetParent());
			if (parent) {
				Transform* parentTransform = parent->GetComponent<Transform>();
				if (parentTransform)
				{
					worldToLocalMat4 = worldToLocalMat4 * parentTransform->worldToLocalMat4;
				}
			}

			std::vector<TreeNode*>* children = getObject()->getChildren();
			if (children) {
				for (auto i : *children)
				{
					Object* obj = dynamic_cast<Object*>(i);
					if (obj) {
						Transform* objTransform = obj->GetComponent<Transform>();
						if (objTransform)
						{
							objTransform->updateWorldToLocalMat4();
						}
					}
				}
			}
		}
	private:


	private:
		Vector2 m_scale = Vector2();
		Vector3 m_rotate = Vector2();

		// 本地转世界
		Mat4 localToWorldMat4 = Mat4();
		Mat4 localMat4 = Mat4();

		Mat4 worldToLocalMat4 = Mat4();

		Mat4 rotateMat = Mat4();

		bool matChanged = false;

		Math::UVector2 rect_position = {{0.5, 0.5}, {0.5, 0.5}};
		Math::UVector2 rect_size = { {0, 100}, {0, 100} };

		Vector2 m_realPosition = { 0, 0 };
		Vector2 m_realSize = { 0, 0 };

		
		Vector2 pivot = { 0.5, 0.5 };
	};
}

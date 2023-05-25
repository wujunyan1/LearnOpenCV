#pragma once
#include "Core.h"
#include "Component.h"
#include "GameObject.h"
#include <vector>

namespace Core 
{
	enum Space
	{
		/// <summary>
		/// 应用相对于本地坐标系的变换。
		/// </summary>
		Self,

		/// <summary>
		/// 应用相对于世界坐标系的变换。
		/// </summary>
		World,
	};

	class Transform : public GameComponent
	{
	public:

		Transform() {
			position = Vector3();
			scale = Vector3(1.0f, 1.0f, 1.0f);
			rotate = Vector3(0.0f, 0.0f, 0.0f);

			localToWorldMat4 = Mat4(1.0f);
			localMat4 = Mat4(1.0f);
			rotateMat = Mat4(1.0f);
			worldToLocalMat4 = Mat4(1.0f);


			matChanged = true;
		}

		Vector3 GetPosition() {
			return Vector3(position.x, position.y, position.z);
		}

		void SetPosition(Vector3 v) {
			position = v;
			matChanged = true;
		}

		void SetScale(Vector3 v) {
			scale = v;
			matChanged = true;
		}

		// https://zhuanlan.zhihu.com/p/45404840
		// https://baike.baidu.com/item/%E6%AC%A7%E6%8B%89%E8%A7%92/1626212
		void SetRotate(Vector3 rotate) {
			rotateMat = Mat4::rotate(rotate.y, Vector3(0.0f, 1.0f, 0.0f));
			rotateMat = Mat4::rotate(rotate.x, Vector3(1.0f, 0.0f, 0.0f)) * rotateMat;
			rotateMat = Mat4::rotate(rotate.z, Vector3(0.0f, 0.0f, 1.0f)) * rotateMat;

			this->rotate = rotate;
			matChanged = true;
		}

		Vector3 GetRotate() {
			return rotate;
		}

		void Rotate(Vector3 rotate, Space space);

		void Quaternion() {

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

		Vector3 getForword() {
			if (matChanged) {
				UpdateLocalMat4();
			}
			return forword;
		}

		Vector3 getRight() {
			if (matChanged) {
				UpdateLocalMat4();
			}
			return right;
		}

		Vector3 getUp() {
			if (matChanged) {
				UpdateLocalMat4();
			}
			return up;
		}


	private:

		void UpdateLocalMat4() {
			// 旋转缩放平移
			localMat4 = Mat4::scale(Vector3(scale.x, scale.y, scale.z));
			localMat4 = rotateMat * localMat4;
			localMat4 =	Mat4::translate(position) * localMat4;


			forword = localMat4 * Vector4(0, 0, 1, 0);
			right = localMat4 * Vector4(1, 0, 0, 0);
			up = localMat4 * Vector4(0, 1, 0, 0);

			updateLocalToWorldMat4();
			updateWorldToLocalMat4();

			matChanged = false;
		}

		void updateLocalToWorldMat4()
		{
			localToWorldMat4 = localMat4;

			Object* parent = dynamic_cast<Object*>(getGameObject()->GetParent());
			if (parent) {
				Transform* parentTransform = parent->GetComponent<Transform>();
				if (parentTransform)
				{
					localToWorldMat4 = parentTransform->localToWorldMat4 * localMat4;
				}
			}

			std::vector<TreeNode*>& children = getGameObject()->getChildren();
			for (auto i : children)
			{
				Object* obj = dynamic_cast<Object*>(i);
				if (obj) {
					Transform* objTransform = obj->GetComponent<Transform>();
					if (objTransform)
					{
						objTransform->updateLocalToWorldMat4();
					}
				}
			}
		}

		void updateWorldToLocalMat4()
		{
			worldToLocalMat4 = rotateMat.clone().transpose();
			worldToLocalMat4 = worldToLocalMat4 * Mat4::translate(-position);
			worldToLocalMat4 = Mat4::scale(Vector3(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z)) * worldToLocalMat4;

			Object* parent = dynamic_cast<Object*>(getGameObject()->GetParent());
			if (parent) {
				Transform* parentTransform = parent->GetComponent<Transform>();
				if (parentTransform)
				{
					worldToLocalMat4 = worldToLocalMat4 * parentTransform->worldToLocalMat4;
				}
			}

			std::vector<TreeNode*>& children = getGameObject()->getChildren();
			for (auto i : children)
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

	private:
		Vector3 position = Vector3();
		Vector3 scale = Vector3();
		Vector3 rotate = Vector3();

		Vector3 forword = Vector3();
		Vector3 right = Vector3();
		Vector3 up = Vector3();

		// 本地转世界
		Mat4 localToWorldMat4 = Mat4();
		Mat4 localMat4 = Mat4();

		Mat4 worldToLocalMat4 = Mat4();

		Mat4 rotateMat = Mat4();

		bool matChanged = false;

	};


}

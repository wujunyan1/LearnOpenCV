#pragma once
#include "Core.h"
#include "Component.h"
#include "Object.h"
#include <vector>

namespace Core 
{
	class Transform : public Component
	{
	public:

		Transform() {
			position = Vector3();
			scale = Vector3(1.0f, 1.0f, 1.0f);
			rotate = Vector3(1.0f, 1.0f, 1.0f);

			localToWorldMat4 = Mat4(1.0f);
			worldMat4 = Mat4(1.0f);
			rotateMat = Mat4(1.0f);


			matChanged = false;

			children = NULL;
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
			rotateMat = Mat4(1.0f);
			rotateMat = rotateMat * Mat4::rotate(rotate.y, Vector3(0.0f, 1.0f, 0.0f));
			rotateMat = rotateMat * Mat4::rotate(rotate.x, Vector3(1.0f, 0.0f, 0.0f));
			rotateMat = rotateMat * Mat4::rotate(rotate.z, Vector3(0.0f, 0.0f, 1.0f));

			this->rotate = rotate;
			matChanged = true;
		}

		Vector3 GetRotate() {
			return rotate;
		}

		void Quaternion() {

		}

		Mat4 GetLocalToWorldMat4() {
			if (matChanged) {
				UpdateLocalMat4();
			}
			return localToWorldMat4;
		}

		Mat4 GetLocalToWorldInverseMat4() {
			if (matChanged) {
				UpdateLocalMat4();
			}
			return localToWorldInverseMat4;
		}

		Mat4 GetWorldMat4() {
			if (matChanged) {
				UpdateLocalMat4();
			}
			return worldMat4;
		}

		void AddChild(Transform* child) {
			if (children == NULL) {
				children = new std::vector<Transform*>();
			}
			children->push_back(child);
		}

		Transform* GetChildByIndex(int index) {
			return children->at(index);
		}

		std::vector<Transform*>* getChildren() {
			return children;
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


		void PreUpdate() {
			if (children == nullptr) {
				return;
			}
			for (auto i : *children)
			{
				i->getObject()->PreUpdate();
			}
		}
		void Update() {
			if (children == nullptr) {
				return;
			}
			for (auto i : *children)
			{
				i->getObject()->Update();
			}
		}
		void LaterUpdate() {
			if (children == nullptr) {
				return;
			}
			for (auto i : *children)
			{
				i->getObject()->LaterUpdate();
			}
		}

		void Render() {
			if (children == nullptr) {
				return;
			}
			for (auto i : *children)
			{
				i->getObject()->Render();
			}
		}

	private:

		void UpdateLocalMat4() {
			localToWorldMat4 = Mat4(1.0f);
			localToWorldMat4 = localToWorldMat4 * Mat4::translate(position);
			localToWorldMat4 = localToWorldMat4 * rotateMat;

			localToWorldMat4 = localToWorldMat4 * Mat4::scale(Vector3(scale.x, scale.y, scale.z));

			forword = localToWorldMat4 * Vector4(0, 0, 1, 0);
			right = localToWorldMat4 * Vector4(1, 0, 0, 0);
			up = localToWorldMat4 * Vector4(0, 1, 0, 0);

			localToWorldInverseMat4 = localToWorldMat4.inverse();

			matChanged = false;
		}

	private:
		Vector3 position = Vector3();
		Vector3 scale = Vector3();
		Vector3 rotate = Vector3();

		Vector3 forword = Vector3();
		Vector3 right = Vector3();
		Vector3 up = Vector3();

		Mat4 localToWorldMat4 = Mat4();
		Mat4 worldMat4 = Mat4();

		Mat4 localToWorldInverseMat4 = Mat4();

		Mat4 rotateMat = Mat4();

		bool matChanged = false;

		std::vector<Transform*>* children;
	};


}

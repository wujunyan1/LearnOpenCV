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
			rotate = Vector3(0.0f, 0.0f, 0.0f);

			localToWorldMat4 = Mat4(1.0f);
			localMat4 = Mat4(1.0f);
			rotateMat = Mat4(1.0f);
			worldToLocalMat4 = Mat4(1.0f);


			matChanged = true;

			children = NULL;
			parent = NULL;
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

		void AddChild(Transform* child) {
			if (children == NULL) {
				children = new std::vector<Transform*>();
			}
			if (child->parent) {
				child->parent->removeChild(child);
			}

			children->push_back(child);
		}

		void removeChild(Transform* child) {
			if (children == NULL) {
				return;
			}
			
			int objId = child->getObject()->GetId();
			std::vector<Transform*>::iterator itor = children->begin();
			while (itor != children->end())
			{
				Transform* c = *itor;
				int id = c->getObject()->GetId();
				if (objId == id) {
					itor = children->erase(itor);
					break;
				}
			}
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

			if (parent) {
				localToWorldMat4 = parent->localToWorldMat4 * localMat4;
			}

			if (children) {
				for (auto i : *children)
				{
					i->updateLocalToWorldMat4();
				}
			}
		}

		void updateWorldToLocalMat4()
		{
			worldToLocalMat4 = rotateMat.clone().transpose();
			worldToLocalMat4 = worldToLocalMat4 * Mat4::translate(-position);
			worldToLocalMat4 = Mat4::scale(Vector3(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z)) * worldToLocalMat4;

			if (parent) {
				worldToLocalMat4 = worldToLocalMat4 * parent->worldToLocalMat4;
			}

			if (children) {
				for (auto i : *children)
				{
					i->updateWorldToLocalMat4();
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

		std::vector<Transform*>* children;
		Transform* parent;
	};


}

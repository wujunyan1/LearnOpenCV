#pragma once

#include <vector>
#include "Component.h"
#include "Core.h"
#include "TreeNode.h"


namespace Core {
	class Object : public TreeNode
	{
	public:
		friend class ObjectManager;

	public:
		Object() : TreeNode()
		{
			componentList = new std::vector<Component*>();
		}

		~Object() {
			for (auto i : *componentList)
			{
				i->OnDestroy();
				delete i;
			}
			delete componentList;
		}

		unsigned int GetId() { return id; }

		template <typename T = Component>
		T* AddComponent()
		{
			T* t = new T();
			componentList->push_back(t);
			t->setObject(this);
			t->Bind();
			return t;
		}

		void RemoveComponent(Component * component)
		{
			std::vector<Component*>::iterator it;
			for (it = componentList->begin(); it != componentList->end();)
			{
				auto i = *it;
				if (i == component) {
					i->UnBind();
					i->OnDestroy();
					componentList->erase(it);
					delete i;
					return;
				}
			}
		}

		template <typename T = Component>
		T* GetComponent()
		{
			for (auto i : *componentList)
			{
				T* t = dynamic_cast<T*>(i);
				if (t != nullptr) {
					return t;
				}
			}
			return nullptr;
		}


		virtual void PreUpdate() {
			for (auto i : *componentList)
			{
				if (i->isActive())
					i->PreUpdate();
			}

			TreeNode::PreUpdate();
		}
		virtual void Update() {
			for (auto i : *componentList)
			{
				if (i->isActive())
					i->Update();
			}

			TreeNode::Update();
		}
		virtual void LaterUpdate() {
			for (auto i : *componentList)
			{
				if (i->isActive())
					i->LaterUpdate();
			}

			TreeNode::LaterUpdate();
		}

		virtual void Render() {
			for (auto i : *componentList)
			{
				if (i->isActive())
					i->Render();
			}

			TreeNode::Render();
		}

	private:
		std::vector<Component*>* componentList;
		String name;
		unsigned int id = 0;
	};


}
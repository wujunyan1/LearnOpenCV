#pragma once

#include <vector>
#include "Component.h"
#include "Core.h"

namespace Core {
	class Object
	{
	public:
		

	public:
		Object(unsigned int id) {
			componentList = new std::vector<Component*>();
			this->id = id;
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


		void PreUpdate() {
			for (auto i : *componentList)
			{
				i->PreUpdate();
			}
		}
		void Update() {
			for (auto i : *componentList)
			{
				i->Update();
			}
		}
		void LaterUpdate() {
			for (auto i : *componentList)
			{
				i->LaterUpdate();
			}
		}

		void Render() {
			for (auto i : *componentList)
			{
				i->Render();
			}
		}

	private:
		std::vector<Component*>* componentList;
		String name;
		unsigned int id;
	};


}
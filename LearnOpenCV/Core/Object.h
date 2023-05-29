#pragma once

#include <vector>
#include "Ref.h"
#include "Core.h"
#include "Component.h"

namespace Core {
	class Component;

	class Object : public Ref
	{
	public:
		friend class ObjectManager;

	public:
		Object() : Ref()
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
			t->Init();
			componentList->push_back(t);
			t->setObject(this);
			t->Bind();
			return t;
		}

		void AddComponent(Component* component)
		{
			if (component->getObject())
			{
				component->UnBind();
			}

			componentList->push_back(component);
			component->setObject(this);
			component->Bind();
			return ;
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

		ui64 getLayer() { return m_layer; };
		void setLayer(ui64 layer) { m_layer = layer; };

		Object* clone();

	protected:
		std::vector<Component*>* componentList;
		String name;
		unsigned int id = 0;

		ui64 m_layer = 1;
	};


}
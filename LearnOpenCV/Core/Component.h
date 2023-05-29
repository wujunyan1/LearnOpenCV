#pragma once
#include "Ref.h"

namespace Core 
{
	class Object;

	class Component : public Ref
	{
	public:
		Component() :Ref() {};

		virtual void Init();
		virtual void OnDestroy();

		virtual void Bind(){}
		virtual void UnBind() {}
		virtual void PreUpdate() {}
		virtual void Update() {}
		virtual void LaterUpdate() {}

		void setObject(Object* o);

		Object* getObject();

		bool isActive() { return b_isActive; };
		void setActive(bool active) { b_isActive = active; };

		virtual Component* clone();

	protected:
		Object* object = nullptr;

		bool b_isActive = true;
	};

	class GameObject;
	class GameComponent : public Component
	{
	public:
		GameObject* getGameObject();

		virtual Component* clone();
	protected:
	};
}


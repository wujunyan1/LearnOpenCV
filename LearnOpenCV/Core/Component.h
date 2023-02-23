#pragma once

namespace Core 
{
	class Object;

	class Component
	{
	public:
		virtual void Init();
		virtual void OnDestroy();

		virtual void Bind(){}
		virtual void UnBind() {}
		virtual void PreUpdate() {}
		virtual void Update() {}
		virtual void LaterUpdate() {}

		virtual void Render(){}

		void setObject(Object* o);

		Object* getObject();

		bool isActive() { return b_isActive; };
		void setActive(bool active) { b_isActive = active; };

	protected:
		Object* object = nullptr;

		bool b_isActive = true;
	};
}


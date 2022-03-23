#pragma once
#include "Core.h"
#include "Component.h"
#include "Camera.h"

namespace Core
{
	class CameraMoveComponent : public Component
	{
	public:
		CameraMoveComponent();

		void Bind();

		void Update();

	private:
		float moveSpeed = 5.0f;
		Core::Vector2 preMousePos = Core::Vector2();
		bool isTouchDown = false;
	};
}

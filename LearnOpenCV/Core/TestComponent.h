#pragma once
#include "Core.h"
#include "Component.h"
#include "Camera.h"

namespace Core
{
	class TestComponent : public GameComponent
	{
	public:
		TestComponent();

		void Bind();

		void Update();

	private:
	};
}

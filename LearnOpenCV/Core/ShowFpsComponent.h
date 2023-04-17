#pragma once
#include "Core.h"
#include "Component.h"
#include "Camera.h"

namespace Core
{
	class ShowFpsComponent : public Component
	{
	public:
		ShowFpsComponent();

		void Bind();

		void Update();

	private:
	};
}

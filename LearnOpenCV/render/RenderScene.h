#pragma once

#include "../math/Math.h"

#include "../Core/Camera.h"

namespace Render
{
	class RenderScene
	{
	public:
		RenderScene() {};
		~RenderScene();

		void beforeRender() {};
		void render(Core::Camera* renderCamera) {};

	private:
	};
}
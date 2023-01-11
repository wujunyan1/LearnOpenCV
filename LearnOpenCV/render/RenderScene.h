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

		virtual void beforeRender() {};
		virtual void render(Core::Camera* renderCamera) {};

	private:
	};
}
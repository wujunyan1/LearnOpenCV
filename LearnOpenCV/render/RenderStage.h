#pragma once

#include "../math/Math.h"

#include "../Core/Camera.h"

namespace Render
{
	class RenderStage
	{
	public:
		RenderStage(unsigned int index): stage(index) {};
		~RenderStage();

		void beforeRender() {};
		void render(Core::Camera* renderCamera) {};

	private:
		unsigned int stage = 0;
	};
}
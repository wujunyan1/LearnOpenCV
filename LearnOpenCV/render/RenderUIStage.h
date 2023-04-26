#pragma once

#include "../math/Math.h"

#include "../Core/Camera.h"

#include "../render/RenderStage.h"

namespace Render
{
	class RenderUIStage : public RenderStage
	{
		friend class RenderStageManager;
	public:
		RenderUIStage(unsigned int index);

		~RenderUIStage();

		void AddRenderCanvas(UI::UICanvas* canvas);

		virtual void render(Core::Camera* renderCamera);

		unsigned int getRenderStage() { return renderStage; };
	};
}
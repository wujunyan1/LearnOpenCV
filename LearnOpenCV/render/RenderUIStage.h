#pragma once

#include "../math/Math.h"

#include "../Core/Camera.h"

#include "../render/RenderStage.h"
#include "../ui/UICanvas.h"

namespace Render
{
	class RenderUIModeComponent : public Component
	{

	};

	class RenderUIStage : public RenderStage
	{
		friend class RenderStageManager;
	public:
		RenderUIStage(unsigned int index);

		~RenderUIStage();

		void AddRenderCanvas(UI::UICanvas* canvas);

		virtual void render(Core::Camera* renderCamera);

		unsigned int getRenderStage() { return renderStage; };

		void setRenderMode(UI::UICanvas::RenderMode mode) 
		{ 
			m_mode = mode;

			switch (m_mode)
			{
			case UI::UICanvas::RenderMode::Camera:

				break;
			case UI::UICanvas::RenderMode::Overlay:

				break;
			case UI::UICanvas::RenderMode::world:

				break;
			default:
				break;
			}

		};
	private:
		UI::UICanvas::RenderMode m_mode;
	};
}
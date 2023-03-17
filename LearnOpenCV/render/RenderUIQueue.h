#pragma once

#include <map>
#include "../math/Math.h"
#include "RenderQueue.h"

namespace UI {
	class UICanvas;
}

namespace Render
{
	class RenderUIQueue: public Render::RenderQueue
	{
	public:
		RenderUIQueue();

		~RenderUIQueue();

		void Render();

		void addRenderCanvas(UI::UICanvas* canvas);

		void clear();

	private:

		// 激活的需要渲染的
		std::vector<UI::UICanvas*>* activeRenderUI;
	};


}
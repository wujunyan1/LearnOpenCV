#include "RenderUIQueue.h"
#include "../ui/UICanvas.h"

namespace Render
{
	RenderUIQueue::RenderUIQueue() : Render::RenderQueue()
	{
		activeRenderUI = new std::vector<UI::UICanvas*>();
	}

	RenderUIQueue::~RenderUIQueue()
	{
		delete activeRenderUI;
		activeRenderUI = nullptr;
	}

	void RenderUIQueue::Render()
	{
		// Ê¹ÓÃÄ³Shader
		shaderProgram->Use();

		for (size_t i = 0; i < index; i++)
		{
			Render::RenderProgram* program = activeRenderProgram->at(i);
			program->Render();
		}
	}

	void RenderUIQueue::addRenderCanvas(UI::UICanvas* canvas)
	{
		if (activeRenderUI->size() <= index)
		{
			activeRenderUI->push_back(canvas);
			index++;
		}
		else
		{
			activeRenderUI->at(index) = canvas;
			index++;
		}
	}

	void RenderUIQueue::clear()
	{
		index = 0;
	}
}
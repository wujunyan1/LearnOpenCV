#include "RenderOpaqueQueue.h"

namespace Logic
{

	RenderOpaqueQueue::~RenderOpaqueQueue()
	{
		
	}

	void RenderOpaqueQueue::Render()
	{
		// Ê¹ÓÃÄ³Shader
		shaderProgram->Use();

		for (size_t i = 0; i < index; i++)
		{
			Render::RenderProgram* program = activeRenderProgram->at(i);
			program->Render();
		}
	}

	void RenderOpaqueQueue::addRenderProgram(Render::RenderProgram* renderProgram)
	{
		if (activeRenderProgram->size() <= index)
		{
			activeRenderProgram->push_back(renderProgram);
			index++;
		}
		else
		{
			activeRenderProgram->at(index) = renderProgram;
			index++;
		}
	}

	void RenderOpaqueQueue::clear()
	{
		index = 0;
	}
}
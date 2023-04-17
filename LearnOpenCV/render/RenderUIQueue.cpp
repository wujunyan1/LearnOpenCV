#include "RenderUIQueue.h"
#include "../ui/UICanvas.h"

namespace Render
{
	RenderUIQueue::RenderUIQueue() : Render::RenderQueue()
	{
		activeRenderUI = new std::vector<UI::UICanvas*>();

		float left = 0.0f;
		float right = 1280.0f;
		float top = 720.0f;
		float bottom = 0.0f;
		float near = -1.0f;
		float far = 1.0f;

		ortho = Mat4(1);
		ortho.m00 = (2.0f) / (right - left);
		ortho.m11 = (2.0f) / (top - bottom);
		ortho.m22 = -(2.0f) / (far - near);
		/*ortho.m30 = -(right + left) / (right - left);
		ortho.m31 = -(top + bottom) / (top - bottom);
		ortho.m32 = -(far + near) / (far - near);*/
	}

	RenderUIQueue::~RenderUIQueue()
	{
		delete activeRenderUI;
		activeRenderUI = nullptr;
	}

	void RenderUIQueue::Render(Core::Camera* camera)
	{
		// Ê¹ÓÃÄ³Shader
		shaderProgram->Use();
		shaderProgram->setMat4("VP", ortho); //camera->getOrthogonalMat4()
		//Mat4 VP = camera->getOrthogonalMat4();
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
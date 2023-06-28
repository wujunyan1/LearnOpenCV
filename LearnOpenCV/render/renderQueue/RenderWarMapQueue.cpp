#include "RenderWarMapQueue.h"

#include "../RenderMain.h"
#include "../ShaderProgram.h"
#include "RenderWarMapQueue.h"

namespace Render
{
	
	RenderWarMapQueue::RenderWarMapQueue()
	{
		renderSort = 0;
		index = 0;
		shaderProgram = nullptr;
		activeRenderProgram = new std::vector<RenderProgram*>();
	}

	RenderWarMapQueue::~RenderWarMapQueue()
	{
		delete activeRenderProgram;
	}

	void RenderWarMapQueue::Render(Core::Camera* camera)
	{
		if (!shaderProgram) 
		{
			return;
		}
		// Ê¹ÓÃÄ³Shader
		shaderProgram->Use();
		
		/*Mat4 op = camera->getOPMat4();
		Mat4 view = camera->getViewMat4();
		Vector4 pos = op * Vector4(0, 0, 0, 1);
		printf("pos %s \n", pos.toString().c_str());*/

		GL_GET_ERROR(shaderProgram->setMat4("OP", camera->getOPMat4()));
		//GL_GET_ERROR(shaderProgram->setMat4("OP", camera->getVPMat4()));
		GL_GET_ERROR(shaderProgram->setMat4("view", camera->getViewMat4()));
		GL_GET_ERROR(shaderProgram->setMat4("ortho", camera->getOrthogonalMat4()));

		Math::AABB& perspectiveAABB = camera->getPerspectiveAABB();
		ui64 mask = camera->getCullingMask();

		std::vector<RenderProgram*> renderProgram;
		for (size_t i = 0; i < index; i++)
		{
			RenderProgram* program = activeRenderProgram->at(i);
			/*Math::AABB& renderAABB = program->getRenderAABB();
			if (perspectiveAABB.isOverlap(renderAABB)) {
				renderProgram.push_back(program);
				program->cameraDistance = (perspectiveAABB._center - renderAABB._center).lenSqr();
			}*/
			program->Render();
		}

		/*for (size_t i = 0; i < renderProgram.size(); i++)
		{
			renderProgram[i]->Render();
		}*/
	}

	void RenderWarMapQueue::clear()
	{
		index = 0;
	}
}
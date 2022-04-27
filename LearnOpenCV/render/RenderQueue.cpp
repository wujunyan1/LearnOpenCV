#include "RenderQueue.h"

namespace Render
{
	std::map<unsigned int, Render::RenderQueue*>* RenderQueueManager::queues = new std::map<unsigned int, Render::RenderQueue*>();

	RenderProgram::RenderProgram()
	{
		meshs = NULL;
		material = NULL;
		shaderProgram = NULL;
	}

	RenderQueue::RenderQueue(ShaderProgram* program)
	{
		index = 0;
		shaderProgram = program;
		activeRenderProgram = new std::vector<RenderProgram*>();
	}

	RenderQueue::~RenderQueue()
	{
		delete activeRenderProgram;
	}

	void RenderQueue::Render()
	{
		// Ê¹ÓÃÄ³Shader
		shaderProgram->Use();

		for (size_t i = 0; i < index; i++)
		{
			RenderProgram* program = activeRenderProgram->at(i);
			program->Render();
		}
	}

	void RenderQueue::addRenderProgram(RenderProgram* renderProgram)
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

	void RenderQueue::clear()
	{
		index = 0;
	}



	void RenderQueueManager::AddRenderQueue(RenderProgram* renderProgram)
	{
		Render::ShaderProgram* program = renderProgram->getShaderProgram();
		unsigned int shaderID = program->GetShader();

		Render::RenderQueue* queue = NULL;
		auto it = queues->find(shaderID);
		if (it == queues->end())
		{
			queue = new Render::RenderQueue(program);
			queues->insert(std::make_pair(shaderID, queue));
		}
		else
		{
			queue = it->second;
		}
		queue->addRenderProgram(renderProgram);
	}

	void RenderQueueManager::RenderQueue()
	{
		std::map<unsigned int, Render::RenderQueue*>::iterator it;
		for (it = queues->begin(); it != queues->end(); it++)
		{
			Render::RenderQueue* queue = it->second;
			queue->Render();
			queue->clear();
		}
	}

}
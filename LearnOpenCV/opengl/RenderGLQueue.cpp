#include "RenderGLQueue.h"
#include "../render/RenderMesh.h"
#include "MaterialGL.h"

namespace OpenGL
{
	std::map<unsigned int, RenderGLQueue*>* RenderGLQueueManager::queues = new std::map<unsigned int, RenderGLQueue*>();


	RenderGLProgram::RenderGLProgram(): Render::RenderProgram()
	{
		material = new MaterialGL();
	}


	RenderGLQueue::RenderGLQueue()
	{
	}

	RenderGLQueue::~RenderGLQueue()
	{
	}

	void RenderGLQueue::Render()
	{

	}


	void RenderGLQueueManager::AddRenderQueue(RenderGLProgram* renderProgram)
	{
		unsigned int vbo = renderProgram->getVBO();

		RenderGLQueue* queue = NULL;
		auto it = queues->find(vbo);
		if (it == queues->end())
		{
			queue = new RenderGLQueue();
			queues->insert(std::make_pair(vbo, queue));
		}
		else
		{
			queue = it->second;
		}
		queue->addRenderProgram(renderProgram);
	}

	void RenderGLQueueManager::RenderQueue()
	{
		std::map<unsigned int, RenderGLQueue*>::iterator it;
		for (it = queues->begin(); it != queues->end(); it++)
		{
			RenderGLQueue* queue = it->second;
			queue->Render();
		}
	}
}
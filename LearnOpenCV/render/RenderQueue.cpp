#include "RenderQueue.h"

namespace Render
{
	std::map<unsigned int, RenderQueue*>* RenderQueueManager::queues = new std::map<unsigned int, RenderQueue*>();

	RenderProgram::RenderProgram()
	{
		mesh = NULL;
		material = NULL;
		shaderProgram = NULL;
		vbo = 0;
	}

	RenderMesh* RenderProgram::createNewRenderMesh(std::string name)
	{
		RenderMesh* mesh = RenderMeshManager::createNewRenderMesh(name);
		this->mesh = mesh;
		return mesh;
	}

	RenderMesh* RenderProgram::loadRenderMesh(std::string name, std::string path)
	{
		RenderMeshManager::loadMeshFile(name, path);
		return this->mesh;
	}

	void RenderQueueManager::AddRenderQueue(RenderProgram* renderProgram)
	{
		unsigned int vbo = renderProgram->getVBO();

		RenderQueue* queue = NULL;
		auto it = queues->find(vbo);
		if (it == queues->end())
		{
			queue = new RenderQueue();
			queues->insert(std::make_pair(vbo, queue));
		}
		else 
		{
			queue = it->second;
		}
		queue->addRenderProgram(renderProgram);
	}
}
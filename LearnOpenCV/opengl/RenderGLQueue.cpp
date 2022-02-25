#include "RenderGLQueue.h"
#include "RenderGLMesh.h"
#include "MaterialGL.h"

namespace OpenGL
{
	std::map<unsigned int, RenderGLQueue*>* RenderGLQueueManager::queues = new std::map<unsigned int, RenderGLQueue*>();


	RenderGLProgram::RenderGLProgram(): Render::RenderProgram()
	{
		material = new MaterialGL();
	}

	Render::RenderMesh* RenderGLProgram::createNewRenderMesh(std::string name)
	{
		RenderGLMesh* mesh = RenderGLMeshManager::createNewRenderMesh(name);
		this->mesh = mesh;
		return mesh;
	}

	Render::RenderMesh* RenderGLProgram::loadRenderMesh(std::string name, std::string path)
	{
		RenderGLMesh* mesh = RenderGLMeshManager::loadMeshFile(name, path);
		this->mesh = mesh;
		return mesh;
	}

	void RenderGLProgram::setShader(const std::string& shaderName)
	{
		shaderProgram = ShaderGLProgram::GetShaderGLProgram(shaderName);
	}

	void RenderGLProgram::Render()
	{
		
	}


	RenderGLQueue::RenderGLQueue(ShaderGLProgram* program)
	{
		shaderProgram = program;
		activeRenderProgram = new std::vector<RenderGLProgram*>();
	}

	RenderGLQueue::~RenderGLQueue()
	{
	}

	void RenderGLQueue::Render()
	{
		GLShader* shader = shaderProgram->GetShaderObj();

		shader->use();

		for (size_t i = 0; i < index; i++)
		{
			RenderGLProgram* program = (RenderGLProgram*)activeRenderProgram->at(i);
			program->Render();

		}
	}


	void RenderGLQueueManager::AddRenderQueue(RenderGLProgram* renderProgram)
	{
		Render::ShaderProgram* program = renderProgram->getShaderProgram();
		unsigned int shaderID = program->GetShader();

		RenderGLQueue* queue = NULL;
		auto it = queues->find(shaderID);
		if (it == queues->end())
		{
			queue = new RenderGLQueue(dynamic_cast<ShaderGLProgram*>(program));
			queues->insert(std::make_pair(shaderID, queue));
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
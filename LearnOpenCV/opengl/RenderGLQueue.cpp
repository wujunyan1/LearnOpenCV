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
		addMesh(mesh);
		return mesh;
	}

	Render::RenderMesh* RenderGLProgram::loadRenderMesh(std::string name, std::string path)
	{
		RenderGLMesh* mesh = RenderGLMeshManager::loadMeshFile(name, path);
		addMesh(mesh);
		return mesh;
	}

	void RenderGLProgram::addModel(Core::AModel* model)
	{
		std::vector<Core::AMesh>& ameshs = model->getMeshs();

		for (auto mesh : ameshs)
		{
			addMesh(mesh.getRenderMesh());
		}
	}

	void RenderGLProgram::setShader(const std::string& shaderName)
	{
		shaderProgram = ShaderGLProgram::GetShaderGLProgram(shaderName);
	}

	void RenderGLProgram::Render()
	{
		// 设置shader 属性
		shaderProgram->RenderMaterial(material);
		// 渲染vao
		for (auto mesh : *meshs)
		{
			mesh->Render();
		}
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
		// 使用某Shader
		shaderProgram->Use();

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
			queue->clear();
		}
	}

}
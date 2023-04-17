#include "RenderQueue.h"

#include "RenderMain.h"
#include "ShaderProgram.h"

namespace Render
{
	std::map<unsigned int, Render::RenderQueue*>* RenderQueueManager::queues = new std::map<unsigned int, Render::RenderQueue*>();

	bool distanceNearToFarCompare(RenderProgram* v1, RenderProgram* v2)
	{
		return v1->cameraDistance > v2->cameraDistance;
	}

	bool distanceFarToNearCompare(RenderProgram* v1, RenderProgram* v2)
	{
		return v1->cameraDistance < v2->cameraDistance;
	}

	RenderProgram::RenderProgram()
	{
		material = new Render::Material();
		shaderProgram = NULL;
	}

	RenderMesh* RenderProgram::createNewRenderMesh(std::string name)
	{
		Render::RenderMesh* mesh = Render::RenderMesh::createNewRenderMesh(name);
		return mesh;
	}

	RenderMesh* RenderProgram::loadRenderMesh(std::string name, std::string path)
	{
		Render::RenderMesh* mesh = Render::RenderMesh::loadMeshFile(name, path);
		return mesh;
	}

	void RenderProgram::setShader(const std::string& shaderName)
	{
		shaderProgram = ShaderProgram::GetShaderProgram(shaderName);
	}

	void RenderProgram::Render()
	{
		if (_model == nullptr)
		{
			return;
		}

		GL_GET_ERROR(glDepthMask(depthTest ? GL_TRUE : GL_FALSE));                                                       //关掉深度测试

		if (blend) {
			GL_GET_ERROR(glEnable(GL_BLEND));	//开混合模式贴图 
		}
		else {
			GL_GET_ERROR(glDisable(GL_BLEND));
		}
		GL_GET_ERROR(glBlendFunc((int)srcBlendFunc, (int)targetBlendFunc));                           //设置混合方式 

		// 设置shader 属性
		shaderProgram->RenderMaterial(material);
		// 渲染vao
		std::vector<Core::ABaseMesh*> ameshs = _model->getMeshs();

		for (size_t i = 0; i < ameshs.size(); i++)
		{
			Core::ABaseMesh* mesh = ameshs[i];
			mesh->getRenderMesh()->Render(shaderProgram, material);
		}
	}

	RenderQueue::RenderQueue()
	{
		renderSort = 0;
		index = 0;
		shaderProgram = nullptr;
		activeRenderProgram = new std::vector<RenderProgram*>();
	}

	RenderQueue::~RenderQueue()
	{
		delete activeRenderProgram;
	}

	void RenderQueue::Render(Core::Camera* camera)
	{
		if (!shaderProgram) 
		{
			return;
		}
		// 使用某Shader
		shaderProgram->Use();
		shaderProgram->setMat4("VP", camera->getVPMat4());
		shaderProgram->setMat4("view", camera->getViewMat4());
		shaderProgram->setMat4("proj", camera->getPerspectiveMat4());

		Math::AABB& perspectiveAABB = camera->getPerspectiveAABB();
		ui64 mask = camera->getCullingMask();

		std::vector<RenderProgram*> renderProgram;
		bool blend = false;
		for (size_t i = 0; i < index; i++)
		{
			RenderProgram* program = activeRenderProgram->at(i);
			Math::AABB& renderAABB = program->getRenderAABB();
			if (perspectiveAABB.isOverlap(renderAABB)) {
				renderProgram.push_back(program);
				program->cameraDistance = (perspectiveAABB._center - renderAABB._center).lenSqr();
				blend = program->blend;
			}
		}

		//todu 不透明物体 从近到远  透明物体 从远到近
		if (blend) {
			std::sort(renderProgram.begin(), renderProgram.end(), distanceFarToNearCompare);
		}
		else {
			std::sort(renderProgram.begin(), renderProgram.end(), distanceNearToFarCompare);
		}

		for (size_t i = 0; i < renderProgram.size(); i++)
		{
			renderProgram[i]->Render();
		}
	}

	void RenderQueue::addRenderProgram(RenderProgram* renderProgram)
	{
		if (!shaderProgram)
		{
			shaderProgram = renderProgram->getShaderProgram();
		}
		// 
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



	void RenderQueueManager::registerRenderQueueCreator(const std::string& type, RenderCreator creator)
	{
		RenderQueueCreatorMap& map = GetRenderQueueCreatorMap();
		map[type] = creator;
	}

	Render::RenderQueue* RenderQueueManager::createRenderQueue(const std::string& type)
	{
		RenderQueueCreatorMap& map = GetRenderQueueCreatorMap();
		const auto itor = map.find(type);
		if (itor == map.end())
		{
			return nullptr;
		}
		return itor->second();
	}

	void RenderQueueManager::AddRenderQueue(RenderProgram* renderProgram)
	{
		Render::ShaderProgram* program = renderProgram->getShaderProgram();
		unsigned int shaderID = program->GetShader();

		Render::RenderQueue* queue = NULL;
		auto it = queues->find(shaderID);
		if (it == queues->end())
		{
			queue = createRenderQueue(renderProgram->getRenderQueueName());  // new Render::RenderQueue();
			queues->insert(std::make_pair(shaderID, queue));
		}
		else
		{
			queue = it->second;
		}
		queue->addRenderProgram(renderProgram);

		std::string queueName = renderProgram->getQueueName();
		
	}

	void RenderQueueManager::RenderQueue()
	{
		std::map<unsigned int, Render::RenderQueue*>::iterator it;
		for (it = queues->begin(); it != queues->end(); it++)
		{
			Render::RenderQueue* queue = it->second;
		}
	}

	void RenderQueueManager::ClearRenderQueue()
	{
		std::map<unsigned int, Render::RenderQueue*>::iterator it;
		for (it = queues->begin(); it != queues->end(); it++)
		{
			Render::RenderQueue* queue = it->second;
			queue->clear();
		}
	}

}
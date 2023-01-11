#include "RenderStage.h"
#include "RenderQueue.h"

using namespace Render;

RenderStage::RenderStage(unsigned int index) : renderStage(index)
{
	queues = new std::map<unsigned int, Render::RenderQueue*>();
}

RenderStage::~RenderStage()
{
	std::map<unsigned int, Render::RenderQueue*>::iterator it;
	for (it = queues->begin(); it != queues->end(); it++)
	{
		Render::RenderQueue* queue = it->second;
		delete queue;
	}
	queues->clear();
	delete queues;
	queues = nullptr;
}

Render::RenderQueue* RenderStage::createRenderQueue(const std::string& type)
{
	RenderQueueManager::RenderQueueCreatorMap& map = RenderQueueManager::GetRenderQueueCreatorMap();
	const auto itor = map.find(type);
	if (itor == map.end())
	{
		return nullptr;
	}
	return itor->second();
}

void RenderStage::AddRenderProgram(RenderProgram* renderProgram)
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

void RenderStage::beforeRender()
{

}

void RenderStage::render(Core::Camera* renderCamera)
{
	std::map<unsigned int, Render::RenderQueue*>::iterator it;
	for (it = queues->begin(); it != queues->end(); it++)
	{
		Render::RenderQueue* queue = it->second;
		queue->Render(renderCamera);
	}
}

void RenderStage::renderEnd()
{
	std::map<unsigned int, Render::RenderQueue*>::iterator it;
	for (it = queues->begin(); it != queues->end(); it++)
	{
		Render::RenderQueue* queue = it->second;
		queue->clear();
	}
}




std::map<unsigned int, RenderStage*> RenderStageManager::stages = std::map<unsigned int, RenderStage*>();
std::vector<RenderStage*> RenderStageManager::renderStages = std::vector<RenderStage*>();


inline int compare(const void* p1, const void* p2)
{
	RenderStage* s1 = (RenderStage*)p1;
	RenderStage* s2 = (RenderStage*)p2;
	
	return s1->getRenderStage() < s2->getRenderStage();
}


void RenderStageManager::AddRenderProgram(RenderProgram* renderProgram)
{
	unsigned int stageIndex = renderProgram->getRenderStage();

	const auto itor = stages.find(stageIndex);
	RenderStage* stage = nullptr;
	if (itor == stages.end())
	{
		stage = new RenderStage(stageIndex);
		stages.insert(std::make_pair(stageIndex, stage));
	}
	else
	{
		stage = itor->second;
	}
	
	stage->AddRenderProgram(renderProgram);
}

void RenderStageManager::beforeRender()
{
	renderStages.clear();

	std::map<unsigned int, RenderStage*>::iterator it;
	for (it = stages.begin(); it != stages.end(); it++)
	{
		RenderStage* stage = it->second;
		stage->beforeRender();

		renderStages.push_back(stage);
	}

	std::sort(renderStages.begin(), renderStages.end(), compare);
}

void RenderStageManager::render(Core::Camera* renderCamera)
{
	std::vector<RenderStage*>::iterator it;
	for (it = renderStages.begin(); it != renderStages.end(); it++)
	{
		RenderStage* stage = *it;
		stage->render(renderCamera);
	}
}

void RenderStageManager::renderEnd()
{
	std::map<unsigned int, RenderStage*>::iterator it;
	for (it = stages.begin(); it != stages.end(); it++)
	{
		RenderStage* stage = it->second;
		stage->renderEnd();
	}
}
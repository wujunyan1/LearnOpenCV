#include "Model.h"
#include "Transform.h"
#include "../math/Triangle.h"
#include "Scene.h"
#include "Camera.h"
#include "../math/Vector4.h"
#include "../math/Vector3.h"
#include "SceneManager.h"

using namespace Core;

Model::Model() : GameComponent()
{
	renderProgram = Render::CreateRenderProgram("test");
	renderProgram->setShader("testShader");
	renderProgram->setRenderQueueName("RenderOpaqueQueue");
	renderProgram->setRenderStage(1000);

	Scene* currScene = SceneManager::GetInstance()->GetCurrScene();
	currScene->addRenderModel(this);
}

Core::Model::~Model()
{
	Scene* currScene = SceneManager::GetInstance()->GetCurrScene();
	currScene->removeRenderModel(getId());
}

void Core::Model::setModel(AModel* model)
{
	renderProgram->setModel(model);
}

void Model::bindRender()
{
}

void Model::Render() 
{
	if (!b_isShow)
		return;
	//Render::RenderBuffer* renderBuffer = Render::RenderBuffer::getInstance();

	Transform* transform = this->getObject()->GetComponent<Transform>();
	//Math::Matrix4& m = transform->GetLocalToWorldMat4();

	Render::Material* material = renderProgram->getMaterial();

	//printf("---------- %p\n", material);

	Math::Vector3 color = Math::Vector3(0.0f, 0.3f, 0.6f);
	//material->setVec3("color", color);

	Math::Matrix4& mat4 = transform->GetLocalToWorldMat4();
	renderProgram->setLocalToWorldMat4(mat4);
	material->setMat4("model", mat4);

	Render::AddRender(renderProgram);
}

void Core::Model::setShader(std::string shaderName)
{
	renderProgram->setShader(shaderName);
}

void Core::Model::setRenderQueue(std::string renderName)
{
	renderProgram->setRenderQueueName(renderName);
}

void Core::Model::setRenderStageIndex(unsigned int stage)
{
	renderProgram->setRenderStage(stage);
}

void Core::Model::setBlend(bool enable)
{
	renderProgram->setBlend(enable);
}

void Core::Model::setBlendFunc(Render::BlendFunc src, Render::BlendFunc target)
{
	renderProgram->setBlendFunc(src, target);
}

void Core::Model::setDepthTest(bool enable)
{
	renderProgram->setDepthTest(enable);
}

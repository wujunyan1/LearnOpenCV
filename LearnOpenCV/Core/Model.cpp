#include "Model.h"
#include "Transform.h"
#include "../math/Triangle.h"
#include "Scene.h"
#include "Camera.h"
#include "../math/Vector4.h"
#include "../math/Vector3.h"

using namespace Core;

Model::Model()
{
	renderProgram = Render::CreateRenderProgram("test");
	renderProgram->setShader("testShader");
	renderProgram->setRenderQueueName("RenderOpaqueQueue");
	renderProgram->setRenderStage(1000);
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

	//if (Math::IsEqual(f_alpha, 0.0f, 0.001f))
	//{
	//	return;
	//}
	//else if (Math::IsEqual(f_alpha, 1.0f, 0.001f))
	//{
	//	printf("xxxxxxxxxx not  alpha %f", f_alpha);
	//	setShader("testShader");  //testShader
	//	setDepthTest(false);
	//	setBlend(false);
	//	//setBlendFunc(Render::BlendFunc::SRC_ALPHA, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);
	//}
	//else 
	//{
	//	printf("---------  alpha %f", f_alpha);
	//	setShader("testBlendShader");  //testBlendShader
	//	setDepthTest(true);
	//	setBlend(true);
	//	setBlendFunc(Render::BlendFunc::SRC_ALPHA, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);
	//}

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

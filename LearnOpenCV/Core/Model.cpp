#include "Model.h"
#include "Transform.h"
#include "../math/Triangle.h"
#include "Scene.h"
#include "Camera.h"
#include "../math/Vector4.h"
#include "../math/Vector3.h"

// #include "../opengl/MaterialGL.h"

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
	//Render::RenderBuffer* renderBuffer = Render::RenderBuffer::getInstance();

	Transform* transform = this->getObject()->GetComponent<Transform>();
	//Math::Matrix4& m = transform->GetLocalToWorldMat4();

	Camera* camera = Scene::getCurrScene()->getMainCamera();
	//Math::Matrix4& v = camera->getViewMat4();
	//Math::Matrix4& p = camera->getPerspectiveMat4();
	//Math::Matrix4& VP = camera->getVPMat4();

	//m.printMat4();

	// Vector4 v4 = m * Vector4(0.5f, 0, 0, 1.0f);
	// Vector4 v5 = m.transpose() * Vector4(0.5f, 0, 0, 1.0f);
	
	//printf("%s \n", v4.toString());

	Render::Material* material = renderProgram->getMaterial();

	//printf("---------- %p\n", material);

	Math::Vector3 color = Math::Vector3(0.0f, 0.3f, 0.6f);
	//material->setVec3("color", color);

	Math::Matrix4& mat4 = transform->GetLocalToWorldMat4();
	renderProgram->setLocalToWorldMat4(mat4);
	material->setMat4("model", mat4);
	/*material->setMat4("VP", camera->getVPMat4());
	material->setMat4("view", camera->getViewMat4());
	material->setMat4("proj", camera->getPerspectiveMat4());*/

	/*material->setMat4("view", v);
	material->setMat4("projection", p);*/


	//Math::Matrix4 mvp = p * v * m;
	//for (size_t i = 0; i < size; i++)
	//{
	//	Math::Triangle<Math::Vector3> t = triangles.at(i);

	//	Math::Vector4 v0 = mvp * Math::Vector4(t.points[0], 1.0f);
	//	Math::Vector4 v1 = mvp * Math::Vector4(t.points[1], 1.0f);
	//	Math::Vector4 v2 = mvp * Math::Vector4(t.points[2], 1.0f);

	//	Math::Vector4 v4 = Math::Vector4(t.points[0], 1.0f);
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

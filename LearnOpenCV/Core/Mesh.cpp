#include "Mesh.h"
#include "Transform.h"
#include "../math/Triangle.h"
#include "Scene.h"
#include "Camera.h"
#include "../math/Vector4.h"
#include "../math/Vector3.h"

using namespace Core;

Mesh::Mesh()
{

}

void Mesh::bindRender()
{
	if (!renderProgram) {
		renderProgram = Render::CreateRenderProgram("test");
		// Render::Material* material = renderProgram->getMaterial();
		renderProgram->setShader("testShader");
	}

	int len = triangles.size();
	int size = len * 9;
	float* data = new float[size];

	for (int i = 0; i < len; i++)
	{
		Math::Triangle<Math::Vector3> t = triangles.at(i);
		
		int index = i * 9;
		data[index] = t.points[0].x;
		data[index + 1] = t.points[0].y;
		data[index + 2] = t.points[0].z;

		data[index + 3] = t.points[1].x;
		data[index + 4] = t.points[1].y;
		data[index + 5] = t.points[1].z;

		data[index + 6] = t.points[2].x;
		data[index + 7] = t.points[2].y;
		data[index + 8] = t.points[2].z;
	}

	Render::RenderMesh* mesh = renderProgram->createNewRenderMesh();
	mesh->BindArrayBufferData(len, size, data);
	mesh->VertexAttribPointer(0, 3, Render::ShaderParamType::SPT_VEC3, false, 3 * sizeof(float), 0);
	//Render::SetVertexAttribPointer(vbo, 0, Render::ShaderParamType::SPT_VEC3, 3, size, data);
}

void Mesh::Render() 
{
	//Render::RenderBuffer* renderBuffer = Render::RenderBuffer::getInstance();

	Transform* transform = this->getObject()->GetComponent<Transform>();
	Math::Matrix4 m = transform->GetLocalToWorldMat4();

	Camera* camera = Scene::getCurrScene()->getMainCamera();
	Math::Matrix4 v = camera->getViewMat4();
	Math::Matrix4 p = camera->getPerspectiveMat4();

	int size = triangles.size();

	Render::Material* material = renderProgram->getMaterial();
	material->setVec3("color", Math::Vector3(0.0f, 0.3f, 0.6f));

	Math::Matrix4 ms = Math::Matrix4::scale(Math::Vector3(0.5f, 0.5f, 0.5f));
	printf("xxxxxxx %p \n", &ms);

	material->setMat4("model", m);
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

	Render::AddRenderQueue(renderProgram);
}
#include "Mesh.h"
#include "Transform.h"
#include "../math/Triangle.h"
#include "../render/RenderBuffer.h"
#include "Scene.h"
#include "Camera.h"
#include "../math/Vector4.h"

using namespace Core;

Mesh::Mesh()
{

}

void Mesh::Render() 
{
	Render::RenderBuffer renderBuffer = Render::RenderBuffer::getInstance();

	Transform* transform = this->getObject()->GetComponent<Transform>();
	Math::Matrix4 m = transform->GetLocalToWorldMat4();

	Camera* camera = Scene::getCurrScene()->getMainCamera();
	Math::Matrix4 v = camera->getViewMat4();
	Math::Matrix4 p = camera->getPerspectiveMat4();

	int size = triangles.size();

	Math::Matrix4 mvp = p * v * m;

	for (size_t i = 0; i < size; i++)
	{
		Math::Triangle<Math::Vector3> t = triangles.at(i);

		Math::Vector4 v0 = mvp * Math::Vector4(t.points[0], 1.0f);
		Math::Vector4 v1 = mvp * Math::Vector4(t.points[1], 1.0f);
		Math::Vector4 v2 = mvp * Math::Vector4(t.points[2], 1.0f);

		Math::Vector4 v4 = Math::Vector4(t.points[0], 1.0f);
		renderBuffer.renderTriangle(
			Math::Triangle<Math::Vector3>(v0 / v0.w, v1 / v1.w, v2 / v2.w),
			colors.at(i)
		);
	}
}
#include "Mesh.h"
#include "Transform.h"
#include "../math/Triangle.h"
#include "../render/RenderBuffer.h"
#include "Scene.h"
#include "Camera.h"

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
	mvp.printMat4();

	for (size_t i = 0; i < size; i++)
	{
		Math::Triangle t = triangles.at(i);

		Math::Vector4 v0 = mvp * Math::Vector4(t.points[0], 1.0f);
		Math::Vector4 v1 = mvp * Math::Vector4(t.points[1], 1.0f);
		Math::Vector4 v2 = mvp * Math::Vector4(t.points[2], 1.0f);

		Math::Vector4 v4 = Math::Vector4(t.points[0], 1.0f);
		printf("v4  == %f %f %f %f \n", v4.x, v4.y, v4.z, v4.w);

		printf("v0  == %f %f %f \n", t.points[0].x, t.points[0].y, t.points[0].z);
		printf("v1  == %f %f %f \n", t.points[1].x, t.points[1].y, t.points[1].z);
		printf("v2  == %f %f %f \n", t.points[2].x, t.points[2].y, t.points[2].z);
		printf("===========================\n");
		printf("v0  == %f %f %f %f \n", v0.x, v0.y, v0.z, v0.w);
		printf("v1  == %f %f %f %f \n", v1.x, v1.y, v1.z, v1.w);
		printf("v2  == %f %f %f %f \n", v2.x, v2.y, v2.z, v2.w);
		renderBuffer.renderTriangle(
			Math::Triangle(v0 / v0.w, v1 / v1.w, v2 / v2.w),
			colors.at(i)
		);
	}
}
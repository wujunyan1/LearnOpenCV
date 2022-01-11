#include "Camera.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Transform.h"

using namespace Core;

Camera::Camera()
{
	printf("Camera");
	//transform = getObject()->GetComponent<Transform>();
}

void Camera::Bind()
{
	transform = getObject()->GetComponent<Transform>();
}

void Camera::init(float fov, float aspect, float near, float far)
{
	this->eye_fov = fov;
	this->aspect_ratio = aspect;
	this->near = near;
	this->far = far;
}

Mat4 Camera::getViewMat4() 
{
	return transform->GetWorldToLocalMat4();
}

Mat4 Camera::getPerspectiveMat4() 
{
	Mat4 perspective = Mat4(
		near, 0, 0, 0,
		0, near, 0, 0,
		0, 0, near + far, -near * far,
		0, 0, 1, 0
	);
	Mat4 orthogonal = getOrthogonalMat4();
	perspective = orthogonal * perspective;

	//float t = std::tan(eye_fov / 2) * near;
	//float r = aspect_ratio * t;

	/*perspective.printMat4();
	m.printMat4();*/
	printf("================\n");
	orthogonal.printMat4();
	perspective.printMat4();
	return perspective;
}

Mat4 Camera::getOrthogonalMat4()
{
	float t = std::tan(eye_fov / 2) * near;
	float r = aspect_ratio * t;

	Mat4 m = Mat4(
		1 / r, 0, 0, 0,
		0, 1 / t, 0, 0,
		0, 0, 1 / (far - near), 0,
		0, 0, 0, 1
	);
	Mat4 trans = Mat4(
		1, 0, 0, 0.5,
		0, 1, 0, 0.5,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	return trans * m;
}
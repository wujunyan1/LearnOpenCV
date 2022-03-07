#include "Camera.h"
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


	float t = std::tan(eye_fov / 2) * near;
	float r = aspect_ratio * t;

	orthogonal = Mat4(
		1 / r, 0, 0, 0,
		0, 1 / t, 0, 0,
		0, 0, 1 / (far - near), 0,
		0, 0, 0, 1
	);

	perspective = Mat4(
		near, 0, 0, 0,
		0, near, 0, 0,
		0, 0, near + far, -near * far,
		0, 0, 1, 0
	);
	perspective = orthogonal * perspective;
}

Mat4 Camera::getViewMat4() 
{
	return transform->GetWorldToLocalMat4();
}

Mat4 Camera::getPerspectiveMat4() 
{
	return perspective;
}

Mat4 Camera::getOrthogonalMat4()
{
	return orthogonal;
}

Mat4 Camera::getVPMat4()
{
	return vp;
}

void Camera::LaterUpdate()
{
	vp = perspective * getViewMat4();
}
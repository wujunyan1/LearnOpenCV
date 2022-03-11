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


	float top = std::tan(eye_fov / 2.0f) * near;
	float right = aspect_ratio * top;
	float bottom = -top;
	float left = -right;

	orthogonal = Mat4(
		2.0f / (right - left), 0, 0, -(right + left) / (right - left),
		0, 2.0f / (top - bottom), 0, -(top + bottom) / (top - bottom),
		0, 0, 1, 0,
		0, 0, 0, 1
	);


	float tanHalfFovy = tan(eye_fov / 2.0f);
	perspective = Mat4(
		1.0f / (aspect * tanHalfFovy), 0, 0, 0,
		0, 1.0f / (tanHalfFovy), 0, 0,
		0, 0, -(near + far) / (far - near), -2.0f * near * far / (far - near),
		0, 0, -1.0f, 0
	);
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
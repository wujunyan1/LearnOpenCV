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


Mat4 Camera::getViewMat4() 
{
	return Mat4();
}
Mat4 Camera::getPerspectiveMat4() 
{
	return Mat4();
}
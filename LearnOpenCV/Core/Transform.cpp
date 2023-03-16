#include "Transform.h"

using namespace Core;

void Transform::Rotate(Vector3 rotate, Space space)
{
	if (space == Space::Self)
	{
		Mat4 rotateMat = Mat4::rotate(rotate.y, Vector3(0.0f, 1.0f, 0.0f));
		rotateMat = Mat4::rotate(rotate.x, Vector3(1.0f, 0.0f, 0.0f)) * rotateMat;
		rotateMat = Mat4::rotate(rotate.z, Vector3(0.0f, 0.0f, 1.0f)) * rotateMat;

		this->rotateMat = this->rotateMat * rotateMat;
	}
	else if (space == Space::World)
	{

	}
}
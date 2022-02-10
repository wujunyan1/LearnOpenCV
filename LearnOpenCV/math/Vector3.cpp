#include "Vector3.h"
#include "Vector1.h"
#include "Vector2.h"
#include "Vector4.h"

using namespace Math;

Vector3::Vector3(Vector1 v1, float _y, float _z)
	: x(v1.x)
	, y(_y)
	, z(_z) {

}

Vector3::Vector3(Vector4 v4)
	: x(v4.x)
	, y(v4.y)
	, z(v4.z) {

}


Vector3::Vector3(Vector2 v2, float _z)
	: x(v2.x)
	, y(v2.y)
	, z(_z)
{

}
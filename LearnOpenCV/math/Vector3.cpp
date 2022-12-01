#include "Vector3.h"
#include "Vector1.h"
#include "Vector2.h"
#include "Vector4.h"

using namespace Math;

const Vector3 Vector3::ZERO(0, 0, 0);
const Vector3 Vector3::ONE(1, 1, 1);
const Vector3 Vector3::HALF(0.5f, 0.5f, 0.5f);
const Vector3 Vector3::UNIT_X(1, 0, 0);
const Vector3 Vector3::UNIT_Y(0, 1, 0);
const Vector3 Vector3::UNIT_Z(0, 0, 1);
const Vector3 Vector3::NEG_UNIT_X(-1, 0, 0);
const Vector3 Vector3::NEG_UNIT_Y(0, -1, 0);
const Vector3 Vector3::NEG_UNIT_Z(0, 0, -1);

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
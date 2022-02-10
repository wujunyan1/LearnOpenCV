#include "Vector2.h"
#include "Vector1.h"
#include "Vector3.h"
#include "Vector4.h"

using namespace Math;

Vector2::Vector2(Vector1 v1, float _y)
	: x(v1.x)
	, y(_y) {

}

Vector2::Vector2(Vector3 v3)
	: x(v3.x)
	, y(v3.y) {

}

Vector2::Vector2(Vector4 v4)
	: x(v4.x)
	, y(v4.y) {

}
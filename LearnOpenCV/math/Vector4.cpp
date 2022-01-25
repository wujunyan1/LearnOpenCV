#include "Vector4.h"
#include "Vector1.h"
#include "Vector2.h"
#include "Vector3.h"

using namespace Math;

Vector4::Vector4(Vector1 v, float _y, float _z, float _w)
	: Vector3(v.x, _y, _z)
	, w(_w) {

}

Vector4::Vector4(Vector2 v, float _z, float _w)
	: Vector3(v.x, v.y, _z)
	, w(_w) {

}

Vector4::Vector4(Vector3 v, float _w)
	: Vector3(v.x, v.y, v.z)
	, w(_w) {

}
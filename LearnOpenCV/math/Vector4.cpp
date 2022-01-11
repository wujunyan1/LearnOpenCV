#include "Vector4.h"
#include "Vector3.h"

using namespace Math;
Vector4::Vector4(Vector3 v, float _w)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = _w;
}
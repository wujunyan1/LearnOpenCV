#include "Vector1.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

using namespace Math;


Vector1::Vector1(Vector2 v2):x(v2.x)
{

}

Vector1::Vector1(Vector3 v3) : x(v3.x)
{

}

Vector1::Vector1(Vector4 v4) : x(v4.x)
{

}
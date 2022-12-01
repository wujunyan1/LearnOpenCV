#include "Base.h"
#include "Math.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Triangle.h"

#define QUAN_EPSILON	(Real)(1e-03)

using namespace Math;


std::string Math::stringFormat(std::string fmt, ...)
{
	char targetString[1024];
	va_list _ArgList;
	__crt_va_start(_ArgList, fmt);
	vsnprintf(targetString, sizeof(targetString), fmt.c_str(), _ArgList);
	__crt_va_end(_ArgList);

	return targetString;
}

unsigned int Math::getUid() {
	return nextId++;
}
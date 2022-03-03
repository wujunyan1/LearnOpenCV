#include "Math.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Triangle.h"

int nextId = 0;


std::string Math::getUid() {
	std::time_t currTime = std::time(0);

	return std::to_string(currTime) + "|" + std::to_string(nextId++);
}
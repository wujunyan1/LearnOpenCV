#include "AABB.h"
#include "Obb.h"

using namespace Math;

Math::AABB::AABB(Obb& obb)
{
	std::vector<Vector3>& points = obb.getPoints();

	AABB(points);
}

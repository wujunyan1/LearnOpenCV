#pragma once
#include "Base.h"
#include "Vector3.h"

namespace Math
{
	class Obb;
	class AABB
	{
	public:
		AABB()
		{
		};

		AABB(std::vector<Vector3> vertices)
		{
			if (vertices.size() < 2)
			{
				return;
			}

			/// todu : 暂时不知道obb算法， 这里先用AABB算法代替
			_min = Vector3(vertices[0]);
			_max = Vector3(vertices[1]);

			for (Vector3 point : vertices)
			{
				_min.x = point.x < _min.x ? point.x : _min.x;
				_min.y = point.y < _min.y ? point.y : _min.y;
				_min.z = point.z < _min.z ? point.z : _min.z;

				_max.x = point.x > _max.x ? point.x : _max.x;
				_max.y = point.y > _max.y ? point.y : _max.y;
				_max.z = point.z > _max.z ? point.z : _max.z;
			}

			_center = (_min + _max) * 0.5;
		};

		AABB(Obb& obb);


		std::string toString()
		{
			char str[1024];
			return std::string(str);
		}

	public:
		Vector3 _center = Vector3();
		Vector3 _min = Vector3();
		Vector3 _max = Vector3();
	};
}

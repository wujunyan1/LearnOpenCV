#pragma once
#include "Base.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Math
{
	class Obb;
	class AABB
	{
	public:
		AABB()
		{
		};

		AABB(std::vector<Vector3>& vertices)
		{
			initVertices(vertices);
		};

		AABB(Obb& obb);


		bool isOverlap(AABB& b)
		{
			if (_max.x < b._min.x || _max.y < b._min.y || _max.z < b._min.z)
			{
				return false;
			}
			if (b._max.x < _min.x || b._max.y < _min.y || b._max.z < _min.z)
			{
				return false;
			}
			return true;
		}

		static bool isOverlap(AABB& a, AABB& b)
		{
			if (a._max.x < b._min.x || a._max.y < b._min.y || a._max.z < b._min.z) 
			{
				return false;
			}
			if (b._max.x < a._min.x || b._max.y < a._min.y || b._max.z < a._min.z)
			{
				return false;
			}
			return true;
		}

		std::string toString()
		{
			char str[1024];
			return std::string(str);
		}

	public:
		void initVertices(std::vector<Vector3>& vertices)
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
		}

		void localToWorld(const Matrix4& mat)
		{
			std::vector<Vector4> points;
			points.push_back(Vector4(_min, 1));
			points.push_back(Vector4(_max.x, _min.y, _min.z, 1));
			points.push_back(Vector4(_min.x, _max.y, _min.z, 1));
			points.push_back(Vector4(_min.x, _min.y, _max.z, 1));

			points.push_back(Vector4(_min.x, _max.y, _max.z, 1));
			points.push_back(Vector4(_max.x, _min.y, _max.z, 1));
			points.push_back(Vector4(_max.x, _max.y, _min.z, 1));
			points.push_back(Vector4(_max, 1));

			std::vector<Vector3> worldPoints;
			for (size_t i = 0; i < 8; i++)
			{
				worldPoints.push_back(mat * points[i]);
			}

			initVertices(worldPoints);
		}

	public:
		Vector3 _center = Vector3();
		Vector3 _min = Vector3();
		Vector3 _max = Vector3();
	};
}

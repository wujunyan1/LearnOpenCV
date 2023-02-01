#pragma once
#include "Base.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Math
{
	class Obb
	{

	public:
		Obb()
		{
		};

		Obb(std::vector<Vector3>& vertices)
		{
			initPoints(vertices);
		};

		void initPoints(std::vector<Vector3>& vertices)
		{
			if (vertices.size() < 2)
			{
				return;
			}

			/// todu : 暂时不知道obb算法， 这里先用AABB算法代替
			Vector3 min = Vector3(vertices[0]);
			Vector3 max = Vector3(vertices[1]);

			for (Vector3 point : vertices)
			{
				min.x = point.x < min.x ? point.x : min.x;
				min.y = point.y < min.y ? point.y : min.y;
				min.z = point.z < min.z ? point.z : min.z;

				max.x = point.x > max.x ? point.x : max.x;
				max.y = point.y > max.y ? point.y : max.y;
				max.z = point.z > max.z ? point.z : max.z;
			}

			_center = (min + max) * 0.5;
			_xAxis = Vector3(1, 0, 0);
			_yAxis = Vector3(0, 1, 0);
			_zAxis = Vector3(0, 0, 1);

			Vector3 extent = (max - min) * 0.5;
			_extentX = Vector3(extent.x, 0, 0);
			_extentY = Vector3(0, extent.y, 0);
			_extentZ = Vector3(0, 0, extent.z);

			updatePoints();
		};

	public:
		inline Obb operator * (const Matrix4 mat)
		{
			Obb result;
			result._center = mat * Vector4(_center, 1);
			result._xAxis = mat * Vector4(_xAxis, 0);
			result._yAxis = mat * Vector4(_yAxis, 0);
			result._zAxis = mat * Vector4(_zAxis, 0);
			result._extentX = mat * Vector4(_extentX, 0);
			result._extentY = mat * Vector4(_extentY, 0);
			result._extentZ = mat * Vector4(_extentZ, 0);

			result.updatePoints();
			return result;
		}

		std::vector<Vector3>& getPoints()
		{
			return points;
		}

		std::string toString()
		{
			char str[1024];
			return std::string(str);
		}

	private:
		void updatePoints()
		{
			points.clear();
			Vector3 left = _center - _extentX;
			Vector3 right = _center + _extentX;

			Vector3 leftTop = left + _extentY;
			Vector3 leftDown = left - _extentY;

			Vector3 rightTop = right + _extentY;
			Vector3 rightDown = right - _extentY;

			points.push_back(leftTop + _extentZ);
			points.push_back(leftTop - _extentZ);
			points.push_back(leftDown + _extentZ);
			points.push_back(leftDown - _extentZ);

			points.push_back(rightTop + _extentZ);
			points.push_back(rightTop - _extentZ);
			points.push_back(rightDown + _extentZ);
			points.push_back(rightDown - _extentZ);
			return;
		}

	private:
		Vector3 _center = Vector3();
		Vector3 _xAxis = Vector3();
		Vector3 _yAxis = Vector3();
		Vector3 _zAxis = Vector3();
		Vector3 _extentX = Vector3();
		Vector3 _extentY = Vector3();
		Vector3 _extentZ = Vector3();
		Vector3 _extents = Vector3();

		std::vector<Vector3> points;
	};
}

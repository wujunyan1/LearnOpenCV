#pragma once
#include "Base.h"
#include "Vector1.h"
#include "Vector3.h"

namespace Math
{
	template <typename T>
	class Triangle
	{
	public:
		Triangle() 
		{
			points[0] = T();
			points[1] = T();
			points[2] = T();
		};
		Triangle(T f, T s, T e){
			points[0] = f;
			points[1] = s;
			points[2] = e;
		}

		Triangle operator * (const T& rhs)
		{
			return Triangle(
				points[0] * rhs,
				points[1] * rhs,
				points[2] * rhs
			);
		}

		bool isIn(const Vector3& point)
		{
			Vector3 v1 = (points[0] - point).cross(points[1] - points[0]);
			Vector3 v2 = (points[1] - point).cross(points[2] - points[1]);
			Vector3 v3 = (points[2] - point).cross(points[0] - points[2]);

			return (v1.z > 0 && v2.z > 0 && v3.z > 0) ||
				(v1.z < 0 && v2.z < 0 && v3.z < 0);
		}

		float getArea()
		{
			Vector3 v = (points[1] - points[0]).cross(points[2] - points[1]);
			return 0.5f * v.len();
		}

		// 重力法
		Vector3 getUV(Vector3 p)
		{
			float area = getArea();

			Triangle t0 = Triangle(p, points[1], points[2]);
			Triangle t1 = Triangle(p, points[0], points[2]);
			//Triangle t2 = Triangle(p, points[0], points[1]);

			float f0 = t0.getArea() / area;
			float f1 = t1.getArea() / area;
			float f2 = 1 - f0 - f1;	// 理论上三个三角形之和就是这个三角形

			return Vector3(f0, f1, f2);
		}

		std::string toString()
		{
			char str[1024];
			snprintf(str, sizeof(str), "{\n p0 = %s\n p1 = %s\n p2 = %s\n }\n", points[0].toString(), points[1].toString(), points[2].toString());
			return std::string(str);
		}

	public:
		T points[3] = {
			T(),T(),T()
		};
	};
}

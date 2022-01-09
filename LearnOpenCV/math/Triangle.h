#pragma once
#include "Base.h"
#include "Vector3.h"

namespace Math
{
	class Triangle
	{
	public:
		Triangle();
		Triangle(Vector3 f, Vector3 s, Vector3 e){
			points[0] = f;
			points[1] = s;
			points[2] = e;
		}

		Triangle operator * (const Vector3& rhs)
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

		// ÖØÁ¦·¨
		Vector3 getUV(Vector3 p)
		{
			float area = getArea();

			Triangle t0 = Triangle(p, points[1], points[2]);
			Triangle t1 = Triangle(p, points[0], points[2]);
			Triangle t2 = Triangle(p, points[0], points[1]);

			return Vector3(
				t0.getArea() / area,
				t1.getArea() / area,
				t2.getArea() / area
			);
		}

	public:
		Vector3 points[3] = {
			Vector3(),Vector3(),Vector3()
		};
	};
}

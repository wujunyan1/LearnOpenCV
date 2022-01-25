#pragma once

#include "Base.h"
#include "Vector2.h"

namespace Math 
{
	class Vector3 : public Vector2
	{
	public:
		Vector3() 
			: Vector2(0.0f, 0.0f)
			, z(0.0f) {

		}

		Vector3(float _x, float _y, float _z)
			: Vector2(_x, _y)
			, z(_z) {

		}

		Vector3(Vector1 v2, float _y = 0.0f, float _z = 0.0f);
		Vector3(Vector2 v2, float _z = 0.0f);
		Vector3(Vector4 v4);

		Vector3& operator = (const Vector3& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}

		Vector3& operator += (const Vector3& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;
			z = z + rhs.z;
			return *this;
		}

		Vector3& operator -= (const Vector3& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;
			z = z - rhs.z;
			return *this;
		}

		Vector3& operator *= (const Vector3& rhs)
		{
			x = x * rhs.x;
			y = y * rhs.y;
			z = z * rhs.z;
			return *this;
		}

		Vector3& operator /= (const Vector3& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;
			z = z / rhs.z;
			return *this;
		}

		Vector3 operator + (const Vector3& rhs)
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Vector3 operator - (const Vector3& rhs)
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Vector3 operator - ()
		{
			return Vector3(-x, -y, -z);
		}

		Vector3 operator * (const Vector3& rhs)
		{
			return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		Vector3 operator * (const float rhs)
		{
			return Vector3(x * rhs, y * rhs, z * rhs);
		}

		Vector3 operator / (const Vector3& rhs)
		{
			return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
		}

		Vector3 operator / (const float rhs)
		{
			return Vector3(x / rhs, y / rhs, z / rhs);
		}

		bool operator == (const Vector3& rhs)
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		bool operator != (const Vector3& rhs)
		{
			return x != rhs.x || y != rhs.y || z != rhs.z;
		}

		float dot(const Vector3& rhs) const
		{
			return (x * rhs.x + y * rhs.y + z * rhs.z);
		}

		Vector3 cross(const Vector3& rhs) const
		{
			Vector3 vec;

			vec.x = y * rhs.z - z * rhs.y;
			vec.y = z * rhs.x - x * rhs.z;
			vec.z = x * rhs.y - y * rhs.x;

			return vec;
		}

		Vector3 add (const Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		void zero()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		float len()
		{
			return Math::Sqrt(x * x + y * y + z * z);
		}

		Vector3 normal()
		{
			float l = this->len();
			return Vector3(x / l, y / l, z / l);
		}

		void normalize()
		{
			float l = this->len();
			x = x / l;
			y = y / l;
			y = y / l;
		}

		std::string toString() 
		{
			char str[1024];
			snprintf(str, sizeof(str), "x = %f, y = %f, z = %f", x, y, z);
			return std::string(str);
		}

	public:
		float z;
	}; 
}


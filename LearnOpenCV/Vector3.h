#pragma once

#include "Math.h"

namespace Math 
{
	class Vector3
	{
	public:
		Vector3() 
			: x(0.0f)
			, y(0.0f)
			, z(0.0f) {

		}

		Vector3(float _x, float _y, float _z)
			: x(_x)
			, y(_y)
			, z(_z) {

		}

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

	public:
		float x;
		float y;
		float z;
	}; 
}


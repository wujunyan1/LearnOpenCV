#pragma once
#include "Base.h"
#include "Vector3.h"

namespace Math {
	class Vector4: public Vector3
	{

	public:
		Vector4()
			: Vector3(0.0f, 0.0f, 0.0f)
			, w(0.0f) {

		}

		Vector4(Vector3 v, float _w)
			: Vector3(v.x, v.y, v.z)
			, w(_w) {

		}

		Vector4(float _x, float _y, float _z, float _w)
			: Vector3(_x, _y, _z)
			, w(_w) {

		}

		Vector4& operator = (const Vector4& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
			return *this;
		}

		Vector4& operator += (const Vector4& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;
			z = z + rhs.z;
			w = w + rhs.w;
			return *this;
		}

		Vector4& operator -= (const Vector4& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;
			z = z - rhs.z;
			w = w - rhs.w;
			return *this;
		}

		Vector4& operator *= (const Vector4& rhs)
		{
			x = x * rhs.x;
			y = y * rhs.y;
			z = z * rhs.z;
			w = w * rhs.w;
			return *this;
		}

		Vector4& operator /= (const Vector4& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;
			z = z / rhs.z;
			w = w / rhs.w;
			return *this;
		}

		Vector4 operator + (const Vector4& rhs)
		{
			return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		Vector4 operator - (const Vector4& rhs)
		{
			return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w + rhs.w);
		}

		Vector4 operator * (const Vector4& rhs)
		{
			return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
		}

		Vector4 operator * (const float rhs)
		{
			return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
		}

		Vector4 operator / (const Vector4& rhs)
		{
			return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.z);
		}

		Vector4 operator / (const float rhs)
		{
			return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
		}

		bool operator == (const Vector4& rhs)
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}

		bool operator != (const Vector4& rhs)
		{
			return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
		}

		float dot(const Vector4& rhs) const
		{
			return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
		}

		float len()
		{
			return Math::Sqrt(x * x + y * y + z * z + w * w);
		}

		Vector4 normal()
		{
			float l = this->len();
			return Vector4(x / l, y / l, z / l, w / l);
		}

		void normalize()
		{
			float l = this->len();
			x = x / l;
			y = y / l;
			y = y / l;
			w = w / l;
		}

	public:
		float w;
	};
}


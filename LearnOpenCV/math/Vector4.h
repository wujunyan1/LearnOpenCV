#pragma once
#include "Base.h"
#include "Vector3.h"

namespace Math {
	class Vector4
	{
	public:
		union
		{
			struct
			{
				float x, y, z, w;
			};
			float m[4];
		};

	public:
		inline Vector4()
			: x(0.0f)
			, y(0.0f)
			, z(0.0f)
			, w(0.0f) {

		}

		Vector4(Vector1 v, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f);

		Vector4(Vector2 v, float _z = 0.0f, float _w = 0.0f);

		Vector4(Vector3 v, float _w = 1.0f);

		inline Vector4(float _x, float _y, float _z, float _w)
			: x(_x)
			, y(_y)
			, z(_z)
			, w(_w) {

		}

		inline Vector4& operator = (const Vector4& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
			return *this;
		}

		inline Vector4& operator += (const Vector4& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;
			z = z + rhs.z;
			w = w + rhs.w;
			return *this;
		}

		inline Vector4& operator -= (const Vector4& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;
			z = z - rhs.z;
			w = w - rhs.w;
			return *this;
		}

		inline Vector4& operator *= (const Vector4& rhs)
		{
			x = x * rhs.x;
			y = y * rhs.y;
			z = z * rhs.z;
			w = w * rhs.w;
			return *this;
		}

		inline Vector4& operator /= (const Vector4& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;
			z = z / rhs.z;
			w = w / rhs.w;
			return *this;
		}

		inline Vector4 operator + (const Vector4& rhs)
		{
			return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		inline Vector4 operator - (const Vector4& rhs)
		{
			return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w + rhs.w);
		}

		inline Vector4 operator * (const Vector4& rhs)
		{
			return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
		}

		inline Vector4 operator * (const float rhs)
		{
			return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
		}

		inline Vector4 operator / (const Vector4& rhs)
		{
			return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.z);
		}

		inline Vector4 operator / (const float rhs)
		{
			return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
		}

		inline bool operator == (const Vector4& rhs)
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}

		inline bool operator != (const Vector4& rhs)
		{
			return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
		}

		inline float operator [] (int row) const
		{
			return m[row];
		}

		inline float dot(const Vector4& rhs) const
		{
			return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
		}

		inline float len()
		{
			return Math::Sqrt(x * x + y * y + z * z + w * w);
		}

		inline Vector4 normal()
		{
			float l = this->len();
			return Vector4(x / l, y / l, z / l, w / l);
		}

		inline void normalize()
		{
			float l = this->len();
			x = x / l;
			y = y / l;
			y = y / l;
			w = w / l;
		}

		inline std::string toString()
		{
			char str[1024];
			snprintf(str, sizeof(str), "x = %f, y = %f, z = %f, w = %f", x, y, z, w);
			return std::string(str);
		}

	public:
	};
}


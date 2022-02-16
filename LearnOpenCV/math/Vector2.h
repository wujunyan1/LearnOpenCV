#pragma once

#include "Base.h"
#include "Vector1.h"

namespace Math 
{
	class Vector2
	{
	public:
		union
		{
			struct
			{
				float x, y;
			};
			float m[2];
		};

	public:
		inline Vector2()
			: x(0.0f)
			, y(0.0f) {

		}

		inline Vector2(float _x, float _y)
			: x(_x)
			, y(_y){

		}

		Vector2(Vector1 v1, float _y = 0.0f);
		Vector2(Vector3 v3);
		Vector2(Vector4 v4);

		inline Vector2& operator = (const Vector2& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		inline Vector2& operator += (const Vector2& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;
			return *this;
		}

		inline Vector2& operator -= (const Vector2& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;
			return *this;
		}

		inline Vector2& operator *= (const Vector2& rhs)
		{
			x = x * rhs.x;
			y = y * rhs.y;
			return *this;
		}

		inline Vector2& operator /= (const Vector2& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;
			return *this;
		}

		inline Vector2 operator + (const Vector2& rhs)
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}

		inline Vector2 operator - (const Vector2& rhs)
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}

		inline Vector2 operator - ()
		{
			return Vector2(-x, -y);
		}

		inline Vector2 operator * (const Vector2& rhs)
		{
			return Vector2(x * rhs.x, y * rhs.y);
		}

		inline Vector2 operator * (const float rhs)
		{
			return Vector2(x * rhs, y * rhs);
		}

		inline Vector2 operator / (const Vector2& rhs)
		{
			return Vector2(x / rhs.x, y / rhs.y);
		}

		inline Vector2 operator / (const float rhs)
		{
			return Vector2(x / rhs, y / rhs);
		}

		inline bool operator == (const Vector2& rhs)
		{
			return x == rhs.x && y == rhs.y;
		}

		inline bool operator != (const Vector2& rhs)
		{
			return x != rhs.x || y != rhs.y;
		}

		inline float dot(const Vector2& rhs) const
		{
			return (x * rhs.x + y * rhs.y);
		}

		inline Vector2 cross(const Vector2& rhs) const
		{
			Vector2 vec;

			vec.x = x * rhs.y;
			vec.y = -y * rhs.x;

			return vec;
		}

		inline Vector2 add (const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		inline void zero()
		{
			x = 0.0f;
			y = 0.0f;
		}

		inline float len()
		{
			return Math::Sqrt(x * x + y * y);
		}

		inline Vector2 normal()
		{
			float l = this->len();
			return Vector2(x / l, y / l);
		}

		inline void normalize()
		{
			float l = this->len();
			x = x / l;
			y = y / l;
		}

		inline std::string toString()
		{
			char str[1024];
			snprintf(str, sizeof(str), "x = %f, y = %f", x, y);
			return std::string(str);
		}

	}; 
}


#pragma once

#include "Base.h"

namespace Math 
{
	class Vector1
	{
	public:
		union
		{
			struct
			{
				float x;
			};
			float m[1];
		};

	public:
		inline Vector1()
			: x(0.0f){

		}

		inline Vector1(float _x)
			: x(_x){

		}

		Vector1(Vector2 v2);
		Vector1(Vector3 v3);
		Vector1(Vector4 v4);

		inline Vector1& operator = (const Vector1& rhs)
		{
			x = rhs.x;
			return *this;
		}

		inline Vector1& operator += (const Vector1& rhs)
		{
			x = x + rhs.x;
			return *this;
		}

		inline Vector1& operator -= (const Vector1& rhs)
		{
			x = x - rhs.x;
			return *this;
		}

		inline Vector1& operator *= (const Vector1& rhs)
		{
			x = x * rhs.x;
			return *this;
		}

		inline Vector1& operator /= (const Vector1& rhs)
		{
			x = x / rhs.x;
			return *this;
		}

		inline Vector1 operator + (const Vector1& rhs)
		{
			return Vector1(x + rhs.x);
		}

		inline Vector1 operator - (const Vector1& rhs)
		{
			return Vector1(x - rhs.x);
		}

		inline Vector1 operator - ()
		{
			return Vector1(-x);
		}

		inline Vector1 operator * (const Vector1& rhs)
		{
			return Vector1(x * rhs.x);
		}

		inline Vector1 operator * (const float rhs)
		{
			return Vector1(x * rhs);
		}

		inline Vector1 operator / (const Vector1& rhs)
		{
			return Vector1(x / rhs.x);
		}

		inline Vector1 operator / (const float rhs)
		{
			return Vector1(x / rhs);
		}

		inline bool operator == (const Vector1& rhs)
		{
			return x == rhs.x;
		}

		inline bool operator != (const Vector1& rhs)
		{
			return x != rhs.x;
		}

		inline float dot(const Vector1& rhs) const
		{
			return (x * rhs.x);
		}

		inline Vector1 cross(const Vector1& rhs) const
		{
			Vector1 vec;

			vec.x = x * rhs.x;

			return vec;
		}

		inline Vector1 add (const Vector1& rhs)
		{
			x += rhs.x;
			return *this;
		}

		inline void zero()
		{
			x = 0.0f;
		}

		inline float len()
		{
			return x;
		}

		inline Vector1 normal()
		{
			return Vector1(1);
		}

		inline void normalize()
		{
			x = 1;
		}

		inline std::string toString()
		{
			char str[1024];
			snprintf(str, sizeof(str), "x = %f", x);
			return std::string(str);
		}
	}; 
}


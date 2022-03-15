#pragma once

#include "Base.h"
#include "Vector1.h"

namespace Math 
{
	template<typename T>
	class Vector2T
	{
	public:
		union
		{
			struct
			{
				T x, y;
			};
			T m[2];
		};

	public:
		inline Vector2T()
			: x(0.0f)
			, y(0.0f) {

		}

		inline Vector2T(T _x, T _y)
			: x(_x)
			, y(_y){

		}

		inline Vector2T& operator = (const Vector2T& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		inline Vector2T& operator += (const Vector2T& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;
			return *this;
		}

		inline Vector2T& operator -= (const Vector2T& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;
			return *this;
		}

		inline Vector2T& operator *= (const Vector2T& rhs)
		{
			x = x * rhs.x;
			y = y * rhs.y;
			return *this;
		}

		inline Vector2T& operator /= (const Vector2T& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;
			return *this;
		}

		inline Vector2T operator + (const Vector2T& rhs)
		{
			return Vector2T(x + rhs.x, y + rhs.y);
		}

		inline Vector2T operator - (const Vector2T& rhs)
		{
			return Vector2T(x - rhs.x, y - rhs.y);
		}

		inline Vector2T operator - ()
		{
			return Vector2T(-x, -y);
		}

		inline Vector2T operator * (const Vector2T& rhs)
		{
			return Vector2T(x * rhs.x, y * rhs.y);
		}

		inline Vector2T operator * (const T rhs)
		{
			return Vector2T(x * rhs, y * rhs);
		}

		inline Vector2T operator / (const Vector2T& rhs)
		{
			return Vector2T(x / rhs.x, y / rhs.y);
		}

		inline Vector2T operator / (const T rhs)
		{
			return Vector2T(x / rhs, y / rhs);
		}

		inline bool operator == (const Vector2T& rhs)
		{
			return x == rhs.x && y == rhs.y;
		}

		inline bool operator != (const Vector2T& rhs)
		{
			return x != rhs.x || y != rhs.y;
		}

		inline T dot(const Vector2T& rhs) const
		{
			return (x * rhs.x + y * rhs.y);
		}

		inline Vector2T cross(const Vector2T& rhs) const
		{
			Vector2T vec;

			vec.x = x * rhs.y;
			vec.y = -y * rhs.x;

			return vec;
		}

		inline Vector2T add (const Vector2T& rhs)
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

		inline T len()
		{
			return Math::Sqrt(x * x + y * y);
		}

		inline Vector2T normal()
		{
			T l = this->len();
			return Vector2T(x / l, y / l);
		}

		inline void normalize()
		{
			T l = this->len();
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


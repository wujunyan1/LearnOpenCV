#pragma once

#include "Base.h"
#include "Vector2.h"

namespace Math 
{
	class UVector2
	{
	public:
		union
		{
			struct
			{
				Vector2 x, y;
			};
			Vector2 m[2];
		};

	public:
		inline UVector2()
			: x(0.0f, 0.0f)
			, y(0.0f, 0.0f) {

		}

		inline UVector2(Vector2 _x, Vector2 _y)
			: x(_x)
			, y(_y){

		}

		inline UVector2& operator = (const UVector2& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		inline UVector2& operator += (const UVector2& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;
			return *this;
		}

		inline UVector2& operator -= (const UVector2& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;
			return *this;
		}

		inline UVector2& operator *= (const UVector2& rhs)
		{
			x = x * rhs.x;
			y = y * rhs.y;
			return *this;
		}

		inline UVector2& operator /= (const UVector2& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;
			return *this;
		}

		inline UVector2 operator + (const UVector2& rhs)
		{
			return UVector2(x + rhs.x, y + rhs.y);
		}

		inline UVector2 operator - (const UVector2& rhs)
		{
			return UVector2(x - rhs.x, y - rhs.y);
		}

		inline UVector2 operator - ()
		{
			return UVector2(-x, -y);
		}

		inline UVector2 operator * (const UVector2& rhs)
		{
			return UVector2(x * rhs.x, y * rhs.y);
		}

		inline UVector2 operator * (const float rhs)
		{
			return UVector2(x * rhs, y * rhs);
		}

		inline UVector2 operator / (const UVector2& rhs)
		{
			return UVector2(x / rhs.x, y / rhs.y);
		}

		inline UVector2 operator / (const float rhs)
		{
			return UVector2(x / rhs, y / rhs);
		}

		inline bool operator == (const UVector2& rhs)
		{
			return x == rhs.x && y == rhs.y;
		}

		inline bool operator != (const UVector2& rhs)
		{
			return x != rhs.x || y != rhs.y;
		}

		inline UVector2 add (const UVector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		inline void zero()
		{
			x.zero();
			y.zero();
		}

		inline float len()
		{
			return 0;
		}

		inline std::string toString()
		{
			char str[1024];
			snprintf(str, sizeof(str), "x = %f %f, y = %f %f", x.x, x.y, y.x, y.y);
			return std::string(str);
		}

	}; 
}


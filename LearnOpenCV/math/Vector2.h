#pragma once

#include "Base.h"
#include "Vector1.h"

namespace Math 
{
	class Vector2 : public Vector1
	{
	public:
		Vector2() 
			: Vector1(0.0f)
			, y(0.0f) {

		}

		Vector2(float _x, float _y)
			: Vector1(_x)
			, y(_y){

		}

		Vector2(Vector1 v1, float _y = 0.0f);
		Vector2(Vector3 v3);
		Vector2(Vector4 v4);

		Vector2& operator = (const Vector2& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		Vector2& operator += (const Vector2& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;
			return *this;
		}

		Vector2& operator -= (const Vector2& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;
			return *this;
		}

		Vector2& operator *= (const Vector2& rhs)
		{
			x = x * rhs.x;
			y = y * rhs.y;
			return *this;
		}

		Vector2& operator /= (const Vector2& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;
			return *this;
		}

		Vector2 operator + (const Vector2& rhs)
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}

		Vector2 operator - (const Vector2& rhs)
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}

		Vector2 operator - ()
		{
			return Vector2(-x, -y);
		}

		Vector2 operator * (const Vector2& rhs)
		{
			return Vector2(x * rhs.x, y * rhs.y);
		}

		Vector2 operator * (const float rhs)
		{
			return Vector2(x * rhs, y * rhs);
		}

		Vector2 operator / (const Vector2& rhs)
		{
			return Vector2(x / rhs.x, y / rhs.y);
		}

		Vector2 operator / (const float rhs)
		{
			return Vector2(x / rhs, y / rhs);
		}

		bool operator == (const Vector2& rhs)
		{
			return x == rhs.x && y == rhs.y;
		}

		bool operator != (const Vector2& rhs)
		{
			return x != rhs.x || y != rhs.y;
		}

		float dot(const Vector2& rhs) const
		{
			return (x * rhs.x + y * rhs.y);
		}

		Vector2 cross(const Vector2& rhs) const
		{
			Vector2 vec;

			vec.x = x * rhs.y;
			vec.y = -y * rhs.x;

			return vec;
		}

		Vector2 add (const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		void zero()
		{
			x = 0.0f;
			y = 0.0f;
		}

		float len()
		{
			return Math::Sqrt(x * x + y * y);
		}

		Vector2 normal()
		{
			float l = this->len();
			return Vector2(x / l, y / l);
		}

		void normalize()
		{
			float l = this->len();
			x = x / l;
			y = y / l;
		}

		std::string toString() 
		{
			char str[1024];
			snprintf(str, sizeof(str), "x = %f, y = %f", x, y);
			return std::string(str);
		}

	public:
		float y;
	}; 
}


#pragma once

#include "Base.h"

namespace Math 
{
	class Vector1
	{
	public:
		Vector1() 
			: x(0.0f){

		}

		Vector1(float _x)
			: x(_x){

		}

		Vector1(Vector2 v2);
		Vector1(Vector3 v3);
		Vector1(Vector4 v4);

		Vector1& operator = (const Vector1& rhs)
		{
			x = rhs.x;
			return *this;
		}

		Vector1& operator += (const Vector1& rhs)
		{
			x = x + rhs.x;
			return *this;
		}

		Vector1& operator -= (const Vector1& rhs)
		{
			x = x - rhs.x;
			return *this;
		}

		Vector1& operator *= (const Vector1& rhs)
		{
			x = x * rhs.x;
			return *this;
		}

		Vector1& operator /= (const Vector1& rhs)
		{
			x = x / rhs.x;
			return *this;
		}

		Vector1 operator + (const Vector1& rhs)
		{
			return Vector1(x + rhs.x);
		}

		Vector1 operator - (const Vector1& rhs)
		{
			return Vector1(x - rhs.x);
		}

		Vector1 operator - ()
		{
			return Vector1(-x);
		}

		Vector1 operator * (const Vector1& rhs)
		{
			return Vector1(x * rhs.x);
		}

		Vector1 operator * (const float rhs)
		{
			return Vector1(x * rhs);
		}

		Vector1 operator / (const Vector1& rhs)
		{
			return Vector1(x / rhs.x);
		}

		Vector1 operator / (const float rhs)
		{
			return Vector1(x / rhs);
		}

		bool operator == (const Vector1& rhs)
		{
			return x == rhs.x;
		}

		bool operator != (const Vector1& rhs)
		{
			return x != rhs.x;
		}

		float dot(const Vector1& rhs) const
		{
			return (x * rhs.x);
		}

		Vector1 cross(const Vector1& rhs) const
		{
			Vector1 vec;

			vec.x = x * rhs.x;

			return vec;
		}

		Vector1 add (const Vector1& rhs)
		{
			x += rhs.x;
			return *this;
		}

		void zero()
		{
			x = 0.0f;
		}

		float len()
		{
			return x;
		}

		Vector1 normal()
		{
			return Vector1(1);
		}

		void normalize()
		{
			x = 1;
		}

		std::string toString() 
		{
			char str[1024];
			snprintf(str, sizeof(str), "x = %f", x);
			return std::string(str);
		}

	public:
		float x;
	}; 
}


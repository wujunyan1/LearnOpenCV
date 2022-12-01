#pragma once

#include "Base.h"

namespace Math 
{
	class Vector3
	{
	public:
		union
		{
			struct
			{
				float x, y, z;
			};
			float m[3];
		};


		static const Vector3 ZERO;					//!< Vec3(0, 0, 0)
		static const Vector3 ONE;					//!< Vec3(1, 1, 1)
		static const Vector3 HALF;					//!< Vec3(0.5f, 0.5f, 0.5f)
		static const Vector3 UNIT_X;				//!< Vec3(1, 0, 0)
		static const Vector3 UNIT_Y;				//!< Vec3(0, 1, 0)
		static const Vector3 UNIT_Z;				//!< Vec3(0, 0, 1)
		static const Vector3 NEG_UNIT_X;			//!< Vec3(-1, 0, 0)
		static const Vector3 NEG_UNIT_Y;			//!< Vec3(0, -1, 0)
		static const Vector3 NEG_UNIT_Z;			//!< Vec3(0, 0, -1)

	public:
		inline Vector3()
			: x(0.0f)
			, y(0.0f)
			, z(0.0f) {

		}

		inline Vector3(float _x, float _y, float _z)
			: x(_x)
			, y(_y)
			, z(_z) {

		}

		Vector3(Vector1 v2, float _y = 0.0f, float _z = 0.0f);
		Vector3(Vector2 v2, float _z = 0.0f);
		Vector3(Vector4 v4);

		inline Vector3& operator = (const Vector3& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}

		inline Vector3& operator += (const Vector3& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;
			z = z + rhs.z;
			return *this;
		}

		inline Vector3& operator -= (const Vector3& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;
			z = z - rhs.z;
			return *this;
		}

		inline Vector3& operator *= (const float value)
		{
			x *= value;
			y *= value;
			z *= value;
			return *this;
		}

		inline Vector3& operator *= (const Vector3& rhs)
		{
			x = x * rhs.x;
			y = y * rhs.y;
			z = z * rhs.z;
			return *this;
		}

		inline Vector3& operator /= (const Vector3& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;
			z = z / rhs.z;
			return *this;
		}

		inline const Vector3& operator + () const
		{
			return *this;
		}

		inline Vector3 operator + (const Vector3& rhs) const
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		inline Vector3 operator - (const Vector3& rhs) const
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		inline Vector3 operator - ()
		{
			return Vector3(-x, -y, -z);
		}

		inline Vector3 operator * (const Vector3& rhs)
		{
			return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		inline Vector3 operator * (const float rhs)
		{
			return Vector3(x * rhs, y * rhs, z * rhs);
		}

		inline Vector3 operator / (const Vector3& rhs)
		{
			return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
		}

		inline Vector3 operator / (const float rhs)
		{
			return Vector3(x / rhs, y / rhs, z / rhs);
		}

		inline bool operator == (const Vector3& rhs)
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		inline bool operator != (const Vector3& rhs)
		{
			return x != rhs.x || y != rhs.y || z != rhs.z;
		}

		inline float operator [] (const int index)
		{
			return m[index];
		}

		inline float dot(const Vector3& rhs) const
		{
			return (x * rhs.x + y * rhs.y + z * rhs.z);
		}

		static inline Vector3 Cross(const Vector3& a, const Vector3& b)
		{
			return {
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			};
		}

		inline Vector3 cross(const Vector3& rhs) const
		{
			Vector3 vec;

			vec.x = y * rhs.z - z * rhs.y;
			vec.y = z * rhs.x - x * rhs.z;
			vec.z = x * rhs.y - y * rhs.x;

			return vec;
		}

		inline Vector3 add (const Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		inline void zero()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		inline float len()
		{
			return Math::Sqrt(x * x + y * y + z * z);
		}

		inline float lenSqr()
		{
			return x * x + y * y + z * z;
		}

		inline Vector3 normal()
		{
			float l = this->len();
			return Vector3(x / l, y / l, z / l);
		}

		inline void normalize()
		{
			float l = this->len();
			x = x / l;
			y = y / l;
			z = z / l;
		}

		inline Vector3 normalizedCopy() const
		{
			Vector3 ret = *this;
			ret.normalize();
			return ret;
		}

		inline std::string toString()
		{
			char str[1024];
			snprintf(str, sizeof(str), "x = %f, y = %f, z = %f", x, y, z);
			return std::string(str);
		}


		inline Vector3 perpendicular() const
		{

			Vector3 perp = this->cross(UNIT_X);

			// Check length
			if (perp.lenSqr() == 0.0)
			{
				/* This vector is the Y axis multiplied by a scalar, so we have
				to use another axis.
				*/
				perp = this->cross(UNIT_Y);
			}
			perp.normalize();

			return perp;
		}

	}; 

	inline const Vector3 operator* (const float rhs, const Vector3 lhs)
	{
		return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
	}
}


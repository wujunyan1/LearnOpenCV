#pragma once

#include "Base.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Math
{
	class Quaternion;
	class Matrix4;
	class Matrix3
	{
	public:
		union
		{
			struct
			{
				float m00, m10, m20;
				float m01, m11, m21;
				float m02, m12, m22;
			};

			float m[9];
		};

		static const Matrix3 IDENTITY;

	public:
		inline Matrix3() : Matrix3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
		{
			
		}

		inline Matrix3(float base) : Matrix3(
			base, 0.0f, 0.0f,
			0.0f, base, 0.0f,
			0.0f, 0.0f, base)
		{
		}

		inline Matrix3(
			float f00, float f01, float f02,
			float f10, float f11, float f12,
			float f20, float f21, float f22)
		{
			m00 = f00; m01 = f01; m02 = f02;
			m10 = f10; m11 = f11; m12 = f12;
			m20 = f20; m21 = f21; m22 = f22;
		}

		Matrix3(Matrix4 mat4);

		inline Matrix3& operator= (const Matrix3& rhs)
		{
			m00 = rhs.m00; m01 = rhs.m01; m02 = rhs.m02;
			m10 = rhs.m10; m11 = rhs.m11; m12 = rhs.m12;
			m20 = rhs.m20; m21 = rhs.m21; m22 = rhs.m22;
			return *this;
		}

		inline Matrix3& operator+= (const float f)
		{
			m00 += f; m01 += f; m02 += f;
			m10 += f; m11 += f; m12 += f;
			m20 += f; m21 += f; m22 += f;

			return *this;
		}

		inline Matrix3& operator+= (const Matrix3& rhs)
		{
			m00 += rhs.m00; m01 += rhs.m01; m02 += rhs.m02;
			m10 += rhs.m10; m11 += rhs.m11; m12 += rhs.m12;
			m20 += rhs.m20; m21 += rhs.m21; m22 += rhs.m22;

			return *this;
		}

		inline Matrix3& operator-= (const float f)
		{
			m00 -= f; m01 -= f; m02 -= f;
			m10 -= f; m11 -= f; m12 -= f;
			m20 -= f; m21 -= f; m22 -= f;

			return *this;
		}

		inline Matrix3& operator-= (const Matrix3& rhs)
		{
			m00 -= rhs.m00; m01 -= rhs.m01; m02 -= rhs.m02;
			m10 -= rhs.m10; m11 -= rhs.m11; m12 -= rhs.m12;
			m20 -= rhs.m20; m21 -= rhs.m21; m22 -= rhs.m22;

			return *this;
		}

		inline Matrix3& operator*= (const float f)
		{
			m00 *= f; m01 *= f; m02 *= f;
			m10 *= f; m11 *= f; m12 *= f;
			m20 *= f; m21 *= f; m22 *= f;

			return *this;
		}

		inline Matrix3& operator *= (const Matrix3& rhs)
		{
			Matrix3 result;

			result.m00 = m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20;
			result.m01 = m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21;
			result.m02 = m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22;

			result.m10 = m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20;
			result.m11 = m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21;
			result.m12 = m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22;

			result.m20 = m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20;
			result.m21 = m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21;
			result.m22 = m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22;

			*this = result;

			return *this;
		}

		inline Matrix3& operator/= (const float f)
		{
			m00 /= f; m01 /= f; m02 /= f;
			m10 /= f; m11 /= f; m12 /= f;
			m20 /= f; m21 /= f; m22 /= f;

			return *this;
		}

		inline bool operator== (const Matrix3& b) const
		{
			// true if all vectors equal to each other
			bool result = m00 == b.m00 && m01 == b.m01 && m02 == b.m02 &&
				m10 == b.m10 && m11 == b.m11 && m12 == b.m12 &&
				m20 == b.m20 && m21 == b.m21 && m22 == b.m22;
			return result;
		}

		inline bool operator!= (const Matrix3& b) const
		{
			// true if any one vector not-equal
			bool result = m00 != b.m00 || m01 != b.m01 || m02 != b.m02 ||
				m10 != b.m10 || m11 != b.m11 || m12 != b.m12 ||
				m20 != b.m20 || m21 != b.m21 || m22 != b.m22;
			return result;
		}

		inline Matrix3 operator+ (const float f) const
		{
			Matrix3 result = *this;
			result += f;
			return result;
		}

		inline friend Matrix3 operator+ (const float f, const Matrix3& a)
		{
			Matrix3 result = a;
			result += f;
			return result;
		}

		inline Matrix3 operator + (const Matrix3& b) const
		{
			Matrix3 result;

			result.m00 = m00 + b.m00;
			result.m01 = m01 + b.m01;
			result.m02 = m02 + b.m02;

			result.m10 = m10 + b.m10;
			result.m11 = m11 + b.m11;
			result.m12 = m12 + b.m12;

			result.m20 = m20 + b.m20;
			result.m21 = m21 + b.m21;
			result.m22 = m22 + b.m22;

			return result;
		}

		inline Matrix3 operator- (const float f) const
		{
			Matrix3 result = *this;
			result -= f;
			return result;
		}

		inline friend Matrix3 operator- (const float f, const Matrix3& a)
		{
			Matrix3 result = a;
			result -= f;
			return result;
		}

		inline Matrix3 operator - (const Matrix3& b) const
		{
			Matrix3 result;

			result.m00 = m00 - b.m00;
			result.m01 = m01 - b.m01;
			result.m02 = m02 - b.m02;

			result.m10 = m10 - b.m10;
			result.m11 = m11 - b.m11;
			result.m12 = m12 - b.m12;

			result.m20 = m20 - b.m20;
			result.m21 = m21 - b.m21;
			result.m22 = m22 - b.m22;
			return result;
		}

		inline friend const Vector3 operator * (const Matrix3& m, const Vector3& v)
		{
			Vector3 result;

			result.x = v.x * m.m00 + v.y * m.m01 + v.z * m.m02;
			result.y = v.x * m.m10 + v.y * m.m11 + v.z * m.m12;
			result.z = v.x * m.m20 + v.y * m.m21 + v.z * m.m22;

			return result;
		}

		inline friend Vector3 operator* (const Vector3& v, const Matrix3& m)
		{
			Vector3 result;

			result.x = v.x * m.m00 + v.y * m.m10 + v.z * m.m20;
			result.y = v.x * m.m01 + v.y * m.m11 + v.z * m.m21;
			result.z = v.x * m.m02 + v.y * m.m12 + v.z * m.m22;

			return result;
		}

		inline Matrix3 operator* (const Matrix3& b) const
		{
			Matrix3 result;

			result.m00 = m00 * b.m00 + m01 * b.m10 + m02 * b.m20;
			result.m01 = m00 * b.m01 + m01 * b.m11 + m02 * b.m21;
			result.m02 = m00 * b.m02 + m01 * b.m12 + m02 * b.m22;

			result.m10 = m10 * b.m00 + m11 * b.m10 + m12 * b.m20;
			result.m11 = m10 * b.m01 + m11 * b.m11 + m12 * b.m21;
			result.m12 = m10 * b.m02 + m11 * b.m12 + m12 * b.m22;

			result.m20 = m20 * b.m00 + m21 * b.m10 + m22 * b.m20;
			result.m21 = m20 * b.m01 + m21 * b.m11 + m22 * b.m21;
			result.m22 = m20 * b.m02 + m21 * b.m12 + m22 * b.m22;

			return result;
		}

		inline Matrix3 operator * (const float f) const
		{
			Matrix3 result;

			result.m00 = m00 * f;
			result.m01 = m01 * f;
			result.m02 = m02 * f;

			result.m10 = m10 * f;
			result.m11 = m11 * f;
			result.m12 = m12 * f;

			result.m20 = m20 * f;
			result.m21 = m21 * f;
			result.m22 = m22 * f;

			return result;
		}

		inline friend const Matrix3 operator* (const float f, const Matrix3& a)
		{
			Matrix3 result;

			result.m00 = f * a.m00;
			result.m01 = f * a.m01;
			result.m02 = f * a.m02;

			result.m10 = f * a.m10;
			result.m11 = f * a.m11;
			result.m12 = f * a.m12;

			result.m20 = f * a.m20;
			result.m21 = f * a.m21;
			result.m22 = f * a.m22;

			return result;
		}

		inline Matrix3 operator / (const float f) const
		{
			Matrix3 result;

			result.m00 = m00 / f;
			result.m01 = m01 / f;
			result.m02 = m02 / f;

			result.m10 = m10 / f;
			result.m11 = m11 / f;
			result.m12 = m12 / f;

			result.m20 = m20 / f;
			result.m21 = m21 / f;
			result.m22 = m22 / f;

			return result;
		}

		inline float operator() (int i, int j) const
		{
			return getRow(i)[j];
		}

		inline Vector3 operator[] (int row) const
		{
			return getRow(row);
		}

		inline Vector3 getRow(int row) const
		{
			const float* p = m + row * 3;
			//return Vector4(p[0], p[1], p[2], p[3]);
			return *(Vector3*)(p);
		}

		// ×ªÖÃ¾ØÕó
		inline Matrix3& transpose ()
		{
			Math::Swap(m01, m10);
			Math::Swap(m02, m20);
			Math::Swap(m12, m21);

			return *this;
		}

		inline Matrix3 inverse() const
		{
			// computes the inverse of a matrix m
			double det = m00 * (m11 * m22 - m21 * m12) -
				m01 * (m10 * m22 - m12 * m20) +
				m02 * (m10 * m21 - m11 * m20);

			double invdet = 1 / det;

			Matrix3 result; // inverse of matrix m
			result.m00 = (m11 * m22 - m21 * m12) * invdet;
			result.m01 = (m02 * m21 - m01 * m22) * invdet;
			result.m02 = (m01 * m12 - m02 * m11) * invdet;
			result.m10 = (m12 * m20 - m10 * m22) * invdet;
			result.m11 = (m00 * m22 - m02 * m20) * invdet;
			result.m12 = (m10 * m02 - m00 * m12) * invdet;
			result.m20 = (m10 * m21 - m20 * m11) * invdet;
			result.m21 = (m20 * m01 - m00 * m21) * invdet;
			result.m22 = (m00 * m11 - m10 * m01) * invdet;

			return *this;
		}

		inline void zero()
		{
			m00 = m01 = m02 = m10 = m11 = m12 = m20 = m21 = m22 = 0;
		}

		inline Matrix3 clone() const
		{
			return Matrix3(
				m00, m01, m02,
				m10, m11, m12,
				m20, m21, m22
			);
		}

		inline void printMat3()
		{
			printf("|-------------|\n");
			printf("| %f %f %f |\n", m00, m01, m02);
			printf("| %f %f %f |\n", m10, m11, m12);
			printf("| %f %f %f |\n", m20, m21, m22);
			printf("|-------------|\n");
		}

		inline static Matrix3 rotate(float radian, Vector3 axis)
		{
			Matrix3 result;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			float fSin, fCos;
			fSin = Math::Sin(radian);
			fCos = Math::Cos(radian);

			result.m00 = (x * x) * (1.0f - fCos) + fCos;
			result.m01 = (x * y) * (1.0f - fCos) - (z * fSin);
			result.m02 = (x * z) * (1.0f - fCos) + (y * fSin);

			result.m10 = (y * x) * (1.0f - fCos) + (z * fSin);
			result.m11 = (y * y) * (1.0f - fCos) + fCos;
			result.m12 = (y * z) * (1.0f - fCos) - (x * fSin);

			result.m20 = (z * x) * (1.0f - fCos) - (y * fSin);
			result.m21 = (z * y) * (1.0f - fCos) + (x * fSin);
			result.m22 = (z * z) * (1.0f - fCos) + fCos;

			return result;
		}

		inline static Matrix3 scale(Vector3 scale)
		{
			Matrix3 result;

			result.m00 = scale.x;
			result.m01 = 0.0f;
			result.m02 = 0.0f;

			result.m10 = 0.0f;
			result.m11 = scale.y;
			result.m12 = 0.0f;

			result.m20 = 0.0f;
			result.m21 = 0.0f;
			result.m22 = scale.z;

			return result;
		}


		float determinant() const;


	};

}

#pragma once

#include "Base.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Math
{
	class Quaternion;
	class Matrix3;
	class Matrix4
	{
	public:
		union
		{
			struct
			{
				float m00, m10, m20, m30;
				float m01, m11, m21, m31;
				float m02, m12, m22, m32;
				float m03, m13, m23, m33;
			};

			float m[16];
		};

		static const Matrix4 IDENTITY;

	public:
		inline Matrix4() : Matrix4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
		{
			
		}

		inline Matrix4(float base) : Matrix4(base, 0.0f, 0.0f, 0.0f,
			0.0f, base, 0.0f, 0.0f,
			0.0f, 0.0f, base, 0.0f,
			0.0f, 0.0f, 0.0f, base)
		{
		}

		inline Matrix4(
			float f00, float f01, float f02, float f03,
			float f10, float f11, float f12, float f13,
			float f20, float f21, float f22, float f23,
			float f30, float f31, float f32, float f33)
		{
			m00 = f00; m01 = f01; m02 = f02; m03 = f03;
			m10 = f10; m11 = f11; m12 = f12; m13 = f13;
			m20 = f20; m21 = f21; m22 = f22; m23 = f23;
			m30 = f30; m31 = f31; m32 = f32; m33 = f33;
		}

		Matrix4(Matrix3 mat3);

		inline Matrix4& operator= (const Matrix4& rhs)
		{
			m00 = rhs.m00; m01 = rhs.m01; m02 = rhs.m02; m03 = rhs.m03;
			m10 = rhs.m10; m11 = rhs.m11; m12 = rhs.m12; m13 = rhs.m13;
			m20 = rhs.m20; m21 = rhs.m21; m22 = rhs.m22; m23 = rhs.m23;
			m30 = rhs.m30; m31 = rhs.m31; m32 = rhs.m32; m33 = rhs.m33;
			return *this;
		}

		inline Matrix4& operator+= (const float f)
		{
			m00 += f; m01 += f; m02 += f; m03 += f;
			m10 += f; m11 += f; m12 += f; m13 += f;
			m20 += f; m21 += f; m22 += f; m23 += f;
			m30 += f; m31 += f; m32 += f; m33 += f;

			return *this;
		}

		inline Matrix4& operator+= (const Matrix4& rhs)
		{
			m00 += rhs.m00; m01 += rhs.m01; m02 += rhs.m02; m03 += rhs.m03;
			m10 += rhs.m10; m11 += rhs.m11; m12 += rhs.m12; m13 += rhs.m13;
			m20 += rhs.m20; m21 += rhs.m21; m22 += rhs.m22; m23 += rhs.m23;
			m30 += rhs.m30; m31 += rhs.m31; m32 += rhs.m32; m33 += rhs.m33;

			return *this;
		}

		inline Matrix4& operator-= (const float f)
		{
			m00 -= f; m01 -= f; m02 -= f; m03 -= f;
			m10 -= f; m11 -= f; m12 -= f; m13 -= f;
			m20 -= f; m21 -= f; m22 -= f; m23 -= f;
			m30 -= f; m31 -= f; m32 -= f; m33 -= f;

			return *this;
		}

		inline Matrix4& operator-= (const Matrix4& rhs)
		{
			m00 -= rhs.m00; m01 -= rhs.m01; m02 -= rhs.m02; m03 -= rhs.m03;
			m10 -= rhs.m10; m11 -= rhs.m11; m12 -= rhs.m12; m13 -= rhs.m13;
			m20 -= rhs.m20; m21 -= rhs.m21; m22 -= rhs.m22; m23 -= rhs.m23;
			m30 -= rhs.m30; m31 -= rhs.m31; m32 -= rhs.m32; m33 -= rhs.m33;

			return *this;
		}

		inline Matrix4& operator*= (const float f)
		{
			m00 *= f; m01 *= f; m02 *= f; m03 *= f;
			m10 *= f; m11 *= f; m12 *= f; m13 *= f;
			m20 *= f; m21 *= f; m22 *= f; m23 *= f;
			m30 *= f; m31 *= f; m32 *= f; m33 *= f;

			return *this;
		}

		inline Matrix4& operator *= (const Matrix4& rhs)
		{
			Matrix4 result;

			result.m00 = m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20 + m03 * rhs.m30;
			result.m01 = m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21 + m03 * rhs.m31;
			result.m02 = m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22 + m03 * rhs.m32;
			result.m03 = m00 * rhs.m03 + m01 * rhs.m13 + m02 * rhs.m23 + m03 * rhs.m33;

			result.m10 = m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20 + m13 * rhs.m30;
			result.m11 = m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31;
			result.m12 = m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32;
			result.m13 = m10 * rhs.m03 + m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33;

			result.m20 = m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20 + m23 * rhs.m30;
			result.m21 = m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31;
			result.m22 = m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32;
			result.m23 = m20 * rhs.m03 + m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33;

			result.m30 = m30 * rhs.m00 + m31 * rhs.m10 + m32 * rhs.m20 + m33 * rhs.m30;
			result.m31 = m30 * rhs.m01 + m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31;
			result.m32 = m30 * rhs.m02 + m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32;
			result.m33 = m30 * rhs.m03 + m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33;

			*this = result;

			return *this;
		}

		inline Matrix4& operator/= (const float f)
		{
			m00 /= f; m01 /= f; m02 /= f; m03 /= f;
			m10 /= f; m11 /= f; m12 /= f; m13 /= f;
			m20 /= f; m21 /= f; m22 /= f; m23 /= f;
			m30 /= f; m31 /= f; m32 /= f; m33 /= f;

			return *this;
		}

		inline bool operator== (const Matrix4& b) const
		{
			// true if all vectors equal to each other
			bool result = m00 == b.m00 && m01 == b.m01 && m02 == b.m02 && m03 == b.m03 &&
			m10 == b.m10 && m11 == b.m11 && m12 == b.m12 && m13 == b.m13 &&
			m20 == b.m20 && m21 == b.m21 && m22 == b.m22 && m23 == b.m23 &&
			m30 == b.m30 && m31 == b.m31 && m32 == b.m32 && m33 == b.m33;
			return result;
		}

		inline bool operator!= (const Matrix4& b) const
		{
			// true if any one vector not-equal
			bool result = m00 != b.m00 || m01 != b.m01 || m02 != b.m02 || m03 != b.m03 ||
			m10 != b.m10 || m11 != b.m11 || m12 != b.m12 || m13 != b.m13 ||
			m20 != b.m20 || m21 != b.m21 || m22 != b.m22 || m23 != b.m23 ||
			m30 != b.m30 || m31 != b.m31 || m32 != b.m32 || m33 != b.m33;
			return result;
		}

		inline Matrix4 operator+ (const float f) const
		{
			Matrix4 result = *this;
			result += f;
			return result;
		}

		inline friend Matrix4 operator+ (const float f, const Matrix4& a)
		{
			Matrix4 result = a;
			result += f;
			return result;
		}

		inline Matrix4 operator + (const Matrix4& b) const
		{
			Matrix4 result;

			result.m00 = m00 + b.m00;
			result.m01 = m01 + b.m01;
			result.m02 = m02 + b.m02;
			result.m03 = m03 + b.m03;

			result.m10 = m10 + b.m10;
			result.m11 = m11 + b.m11;
			result.m12 = m12 + b.m12;
			result.m13 = m13 + b.m13;

			result.m20 = m20 + b.m20;
			result.m21 = m21 + b.m21;
			result.m22 = m22 + b.m22;
			result.m23 = m23 + b.m23;

			result.m30 = m30 + b.m30;
			result.m31 = m31 + b.m31;
			result.m32 = m32 + b.m32;
			result.m33 = m33 + b.m33;

			return result;
		}

		inline Matrix4 operator- (const float f) const
		{
			Matrix4 result = *this;
			result -= f;
			return result;
		}

		inline friend Matrix4 operator- (const float f, const Matrix4& a)
		{
			Matrix4 result = a;
			result -= f;
			return result;
		}

		inline Matrix4 operator - (const Matrix4& b) const
		{
			Matrix4 result;

			result.m00 = m00 - b.m00;
			result.m01 = m01 - b.m01;
			result.m02 = m02 - b.m02;
			result.m03 = m03 - b.m03;

			result.m10 = m10 - b.m10;
			result.m11 = m11 - b.m11;
			result.m12 = m12 - b.m12;
			result.m13 = m13 - b.m13;

			result.m20 = m20 - b.m20;
			result.m21 = m21 - b.m21;
			result.m22 = m22 - b.m22;
			result.m23 = m23 - b.m23;

			result.m30 = m30 - b.m30;
			result.m31 = m31 - b.m31;
			result.m32 = m32 - b.m32;
			result.m33 = m33 - b.m33;

			return result;
		}

		inline friend const Vector4 operator * (const Matrix4& m, const Vector4& v)
		{
			Vector4 result;

			result.x = v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + v.w * m.m03;
			result.y = v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + v.w * m.m13;
			result.z = v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + v.w * m.m23;
			result.w = v.x * m.m30 + v.y * m.m31 + v.z * m.m32 + v.w * m.m33;

			return result;
		}

		inline friend Vector3 operator* (const Vector3& v, const Matrix4& m)
		{
			Vector3 result;

			result.x = v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + m.m30;
			result.y = v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + m.m31;
			result.z = v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + m.m32;

			return result;
		}

		inline Matrix4 operator* (const Matrix4& b) const
		{
			Matrix4 result;

			result.m00 = m00 * b.m00 + m01 * b.m10 + m02 * b.m20 + m03 * b.m30;
			result.m01 = m00 * b.m01 + m01 * b.m11 + m02 * b.m21 + m03 * b.m31;
			result.m02 = m00 * b.m02 + m01 * b.m12 + m02 * b.m22 + m03 * b.m32;
			result.m03 = m00 * b.m03 + m01 * b.m13 + m02 * b.m23 + m03 * b.m33;

			result.m10 = m10 * b.m00 + m11 * b.m10 + m12 * b.m20 + m13 * b.m30;
			result.m11 = m10 * b.m01 + m11 * b.m11 + m12 * b.m21 + m13 * b.m31;
			result.m12 = m10 * b.m02 + m11 * b.m12 + m12 * b.m22 + m13 * b.m32;
			result.m13 = m10 * b.m03 + m11 * b.m13 + m12 * b.m23 + m13 * b.m33;

			result.m20 = m20 * b.m00 + m21 * b.m10 + m22 * b.m20 + m23 * b.m30;
			result.m21 = m20 * b.m01 + m21 * b.m11 + m22 * b.m21 + m23 * b.m31;
			result.m22 = m20 * b.m02 + m21 * b.m12 + m22 * b.m22 + m23 * b.m32;
			result.m23 = m20 * b.m03 + m21 * b.m13 + m22 * b.m23 + m23 * b.m33;

			result.m30 = m30 * b.m00 + m31 * b.m10 + m32 * b.m20 + m33 * b.m30;
			result.m31 = m30 * b.m01 + m31 * b.m11 + m32 * b.m21 + m33 * b.m31;
			result.m32 = m30 * b.m02 + m31 * b.m12 + m32 * b.m22 + m33 * b.m32;
			result.m33 = m30 * b.m03 + m31 * b.m13 + m32 * b.m23 + m33 * b.m33;

			return result;
		}

		inline Matrix4 operator * (const float f) const
		{
			Matrix4 result;

			result.m00 = m00 * f;
			result.m01 = m01 * f;
			result.m02 = m02 * f;
			result.m03 = m03 * f;

			result.m10 = m10 * f;
			result.m11 = m11 * f;
			result.m12 = m12 * f;
			result.m13 = m13 * f;

			result.m20 = m20 * f;
			result.m21 = m21 * f;
			result.m22 = m22 * f;
			result.m23 = m23 * f;

			result.m30 = m30 * f;
			result.m31 = m31 * f;
			result.m32 = m32 * f;
			result.m33 = m33 * f;

			return result;
		}

		inline friend const Matrix4 operator* (const float f, const Matrix4& a)
		{
			Matrix4 result;

			result.m00 = f * a.m00;
			result.m01 = f * a.m01;
			result.m02 = f * a.m02;
			result.m03 = f * a.m03;

			result.m10 = f * a.m10;
			result.m11 = f * a.m11;
			result.m12 = f * a.m12;
			result.m13 = f * a.m13;

			result.m20 = f * a.m20;
			result.m21 = f * a.m21;
			result.m22 = f * a.m22;
			result.m23 = f * a.m23;

			result.m30 = f * a.m30;
			result.m31 = f * a.m31;
			result.m32 = f * a.m32;
			result.m33 = f * a.m33;

			return result;
		}

		inline Matrix4 operator / (const float f) const
		{
			Matrix4 result;

			result.m00 = m00 / f;
			result.m01 = m01 / f;
			result.m02 = m02 / f;
			result.m03 = m03 / f;

			result.m10 = m10 / f;
			result.m11 = m11 / f;
			result.m12 = m12 / f;
			result.m13 = m13 / f;

			result.m20 = m20 / f;
			result.m21 = m21 / f;
			result.m22 = m22 / f;
			result.m23 = m23 / f;

			result.m30 = m30 / f;
			result.m31 = m31 / f;
			result.m32 = m32 / f;
			result.m33 = m33 / f;

			return result;
		}

		inline float operator() (int i, int j) const
		{
			return getRow(i)[j];
		}

		inline Vector4 operator[] (int row) const
		{
			return getRow(row);
		}

		inline Vector4 getRow(int row) const
		{
			const float* p = m + row * 4;
			//return Vector4(p[0], p[1], p[2], p[3]);
			return *(Vector4*)(p);
		}

		// 转置矩阵
		inline Matrix4& transpose ()
		{
			Math::Swap(m01, m10);
			Math::Swap(m02, m20);
			Math::Swap(m03, m30);
			Math::Swap(m12, m21);
			Math::Swap(m13, m31);
			Math::Swap(m23, m32);

			return *this;
		}

		inline Matrix4 inverse() const
		{
			Matrix4 result;

			float _m00 = m00, _m01 = m01, _m02 = m02, _m03 = m03;
			float _m10 = m10, _m11 = m11, _m12 = m12, _m13 = m13;
			float _m20 = m20, _m21 = m21, _m22 = m22, _m23 = m23;
			float _m30 = m30, _m31 = m31, _m32 = m32, _m33 = m33;

			float v0 = _m20 * _m31 - _m21 * _m30;
			float v1 = _m20 * _m32 - _m22 * _m30;
			float v2 = _m20 * _m33 - _m23 * _m30;
			float v3 = _m21 * _m32 - _m22 * _m31;
			float v4 = _m21 * _m33 - _m23 * _m31;
			float v5 = _m22 * _m33 - _m23 * _m32;

			float t00 = +(v5 * _m11 - v4 * _m12 + v3 * _m13);
			float t10 = -(v5 * _m10 - v2 * _m12 + v1 * _m13);
			float t20 = +(v4 * _m10 - v2 * _m11 + v0 * _m13);
			float t30 = -(v3 * _m10 - v1 * _m11 + v0 * _m12);

			float detInv = 1.0f / (t00 * _m00 + t10 * _m01 + t20 * m02 + t30 * m03);

			result.m00 = t00 * detInv;
			result.m10 = t10 * detInv;
			result.m20 = t20 * detInv;
			result.m30 = t30 * detInv;

			result.m01 = -(v5 * _m01 - v4 * _m02 + v3 * _m03) * detInv;
			result.m11 = +(v5 * _m00 - v2 * _m02 + v1 * _m03) * detInv;
			result.m21 = -(v4 * _m00 - v2 * _m01 + v0 * _m03) * detInv;
			result.m31 = +(v3 * _m00 - v1 * _m01 + v0 * _m02) * detInv;

			v0 = _m10 * _m31 - _m11 * _m30;
			v1 = _m10 * _m32 - _m12 * _m30;
			v2 = _m10 * _m33 - _m13 * _m30;
			v3 = _m11 * _m32 - _m12 * _m31;
			v4 = _m11 * _m33 - _m13 * _m31;
			v5 = _m12 * _m33 - _m13 * _m32;

			result.m02 = +(v5 * _m01 - v4 * _m02 + v3 * _m03) * detInv;
			result.m12 = -(v5 * _m00 - v2 * _m02 + v1 * _m03) * detInv;
			result.m22 = +(v4 * _m00 - v2 * _m01 + v0 * _m03) * detInv;
			result.m32 = -(v3 * _m00 - v1 * _m01 + v0 * _m02) * detInv;

			v0 = _m21 * _m10 - _m20 * _m11;
			v1 = _m22 * _m10 - _m20 * _m12;
			v2 = _m23 * _m10 - _m20 * _m13;
			v3 = _m22 * _m11 - _m21 * _m12;
			v4 = _m23 * _m11 - _m21 * _m13;
			v5 = _m23 * _m12 - _m22 * _m13;

			result.m03 = -(v5 * _m01 - v4 * _m02 + v3 * _m03) * detInv;
			result.m13 = +(v5 * _m00 - v2 * _m02 + v1 * _m03) * detInv;
			result.m23 = -(v4 * _m00 - v2 * _m01 + v0 * _m03) * detInv;
			result.m33 = +(v3 * _m00 - v1 * _m01 + v0 * _m02) * detInv;

			return *this;
		}

		inline void zero()
		{
			m00 = m01 = m02 = m03 = m10 = m11 = m12 = m13 = m20 = m21 = m22 = m23 = m30 = m31 = m32 = m33 = 0;
		}

		inline Matrix4 clone() const
		{
			return Matrix4(
				m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33
			);
		}

		inline void printMat4()
		{
			printf("|-------------|\n");
			printf("| %f %f %f %f |\n", m00, m01, m02, m03);
			printf("| %f %f %f %f |\n", m10, m11, m12, m13);
			printf("| %f %f %f %f |\n", m20, m21, m22, m23);
			printf("| %f %f %f %f |\n", m30, m31, m32, m33);
			printf("|-------------|\n");
		}

		inline static Matrix4 rotate(float radian, Vector3 axis)
		{
			Matrix4 result;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			float fSin, fCos;
			fSin = Math::Sin(radian);
			fCos = Math::Cos(radian);

			result.m00 = (x * x) * (1.0f - fCos) + fCos;
			result.m01 = (x * y) * (1.0f - fCos) - (z * fSin);
			result.m02 = (x * z) * (1.0f - fCos) + (y * fSin);
			result.m03 = 0.0f;

			result.m10 = (y * x) * (1.0f - fCos) + (z * fSin);
			result.m11 = (y * y) * (1.0f - fCos) + fCos;
			result.m12 = (y * z) * (1.0f - fCos) - (x * fSin);
			result.m13 = 0.0f;

			result.m20 = (z * x) * (1.0f - fCos) - (y * fSin);
			result.m21 = (z * y) * (1.0f - fCos) + (x * fSin);
			result.m22 = (z * z) * (1.0f - fCos) + fCos;
			result.m23 = 0.0f;

			result.m30 = 0.0f;
			result.m31 = 0.0f;
			result.m32 = 0.0f;
			result.m33 = 1.0f;

			return result;
		}

		inline static Matrix4 scale(Vector3 scale)
		{
			Matrix4 result;

			result.m00 = scale.x;
			result.m01 = 0.0f;
			result.m02 = 0.0f;
			result.m03 = 0.0f;

			result.m10 = 0.0f;
			result.m11 = scale.y;
			result.m12 = 0.0f;
			result.m13 = 0.0f;

			result.m20 = 0.0f;
			result.m21 = 0.0f;
			result.m22 = scale.z;
			result.m23 = 0.0f;

			result.m30 = 0.0f;
			result.m31 = 0.0f;
			result.m32 = 0.0f;
			result.m33 = 1.0f;

			return result;
		}

		inline static Matrix4 translate(Vector3 pos)
		{
			Matrix4 result;

			result.m00 = 1.0f;
			result.m01 = 0.0f;
			result.m02 = 0.0f;
			result.m03 = pos.x;

			result.m10 = 0.0f;
			result.m11 = 1.0f;
			result.m12 = 0.0f;
			result.m13 = pos.y;

			result.m20 = 0.0f;
			result.m21 = 0.0f;
			result.m22 = 1.0f;
			result.m23 = pos.z;

			result.m30 = 0.0f;
			result.m31 = 0.0f;
			result.m32 = 0.0f;
			result.m33 = 1.0f;

			return result;
		}


		float determinant() const;

		// 从矩阵中分离出缩放，旋转和平移信息。
		bool decompose(Vector3* scale, Quaternion* rotation, Vector3* translation) const;

	};

}

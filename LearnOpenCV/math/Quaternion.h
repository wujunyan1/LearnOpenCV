#pragma once

#include "Base.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

namespace Math
{
	class Quaternion
	{
	public:
		union
		{
			struct
			{
				float w, x, y, z;
			};

			float m[4];
		};

		static const Quaternion IDENTITY;		//!< Quan(1, 0, 0, 0)
		static const Quaternion INVALID;		//!< Quan(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL)
		static const Quaternion ZERO;

		static Quaternion Create(float w, float x, float y, float z) {
			return Quaternion(w, x, y, z);
		}

	public:
		inline Quaternion()
			: w(1)
			, x(0)
			, y(0)
			, z(0)
		{
		}

		inline Quaternion(const Quaternion& quan)
			: w(quan.w)
			, x(quan.x)
			, y(quan.y)
			, z(quan.z)
		{
		}

		inline Quaternion(const float* pf)
		{
			w = pf[0];
			x = pf[1];
			y = pf[2];
			z = pf[3];
		}

		inline Quaternion(float fw, float fx, float fy, float fz)
			: w(fw)
			, x(fx)
			, y(fy)
			, z(fz)
		{
		}

		inline Quaternion(const Vector3& vAixs, float radian)
		{
			rotateAxis(vAixs, radian);
		}

		inline float& operator[] (int index)
		{
			return m[index];
		}

		inline const float& operator[] (int index) const
		{
			return m[index];
		}

		inline Quaternion& operator= (const Quaternion& quan)
		{
			w = quan.w;
			x = quan.x;
			y = quan.y;
			z = quan.z;

			return *this;
		}

		inline operator float* ()
		{
			return m;
		}

		inline operator const float* () const
		{
			return m;
		}

		//inline operator std::array<float, 4>() const
		//{
		//	return { { w, x, y, z } };
		//}

		inline Quaternion& operator += (const Quaternion& q)
		{
			w += q.w;
			x += q.x;
			y += q.y;
			z += q.z;

			return *this;
		}

		inline Quaternion& operator -= (const Quaternion& q)
		{
			w -= q.w;
			x -= q.x;
			y -= q.y;
			z -= q.z;

			return *this;
		}

		inline Quaternion& operator *= (const Quaternion& q)
		{
			w = w * q.w - x * q.x - y * q.y - z *q.z;
			x = w * q.x + x * q.w + z * q.y - y *q.z;
			y = w * q.y + y * q.w + x * q.z - z *q.x;
			z = w * q.z + z * q.w + y * q.x - x *q.y;

			return *this;
		}

		inline Quaternion& operator *= (float f)
		{
			w *= f;
			x *= f;
			y *= f;
			z *= f;

			return *this;
		}

		inline Quaternion& operator /= (float f)
		{
			float fInv = 1.0f / f;
			w *= fInv;
			x *= fInv;
			y *= fInv;
			z *= fInv;

			return *this;
		}

		inline float* ptr()
		{
			return &w;
		}

		inline const float* ptr() const
		{
			return &w;
		}

		inline const Quaternion& operator + () const
		{
			return *this;
		}

		inline Quaternion operator - () const
		{
			return Quaternion(-w, -x, -y, -z);
		}

		inline bool operator == (const Quaternion& b) const
		{
			return (w==b.w && x==b.x && y==b.y && z==b.z);
		}

		inline bool operator != (const Quaternion& b) const
		{
			return !(w==b.w && x==b.x && y==b.y && z==b.z);
		}

		inline Quaternion operator + (const Quaternion& b) const
		{
			Quaternion quan;

			quan.w = w + b.w;
			quan.x = x + b.x;
			quan.y = y + b.y;
			quan.z = z + b.z;

			return quan;
		}

		inline Quaternion operator- (const Quaternion& b) const
		{
			Quaternion quan;

			quan.w = w - b.w;
			quan.x = x - b.x;
			quan.y = y - b.y;
			quan.z = z - b.z;

			return quan;
		}

		inline friend Quaternion operator* (const float f, const Quaternion& q)
		{
			Quaternion result;

			result.w = f * q.w;
			result.x = f * q.x;
			result.y = f * q.y;
			result.z = f * q.z;

			return result;
		}

		inline Quaternion operator* (const float f) const
		{
			Quaternion result;

			result.w = f * w;
			result.x = f * x;
			result.y = f * y;
			result.z = f * z;

			return result;
		}

		//′?3?·¨ó????ó?3Dò??o?ê?·′μ?,???óê?local*parent,′??aparent*local;
		inline Quaternion operator* (const Quaternion& b) const
		{
			/* standard define
			Quan quan;
			quan.w = w * b.w - x * b.x - y * b.y - z *b.z;
			quan.x = w * b.x + x * b.w + z * b.y - y *b.z;
			quan.y = w * b.y + y * b.w + x * b.z - z *b.x;
			quan.z = w * b.z + z * b.w + y * b.x - x *b.y;
			*/

			Quaternion quan;
			quan.w = w * b.w - x * b.x - y * b.y - z *b.z;
			quan.x = w * b.x + x * b.w + y * b.z - z *b.y;
			quan.y = w * b.y + y * b.w + z * b.x - x *b.z;
			quan.z = w * b.z + z * b.w + x * b.y - y *b.x;

			return quan;
		}

		inline static Vector3 multiplyVec3(const Quaternion& q, const Vector3& v)
		{
			return q * v;
		}

		inline Vector3 operator* (const Vector3& v) const
		{
			// nVidia SDK implementation
			Vector3 uv, uuv;
			Vector3 qvec(x, y, z);
			uv = qvec.cross(v);
			uuv = qvec.cross(uv);
			uv *= 2.0f * w;
			uuv *= 2.0f;

			return v + uv + uuv;
		}

		inline Vector4 operator* (const Vector4& v) const
		{
			// nVidia SDK implementation
			Vector3 vec(v);
			Vector3 uv, uuv;
			Vector3 qvec(x, y, z);
			uv = qvec.cross(vec);
			uuv = qvec.cross(uv);
			uv *= 2.0f * w;
			uuv *= 2.0f;

			return Vector4(vec + uv + uuv, 1.0f);
		}

		inline Quaternion operator/ (const float f) const
		{
			Quaternion quan;
			float fInv = 1.0f / f;

			quan.w = w * fInv;
			quan.x = x * fInv;
			quan.y = y * fInv;
			quan.z = z * fInv;

			return quan;
		}

		inline friend Quaternion operator/ (const float f, const Quaternion& a)
		{
			Quaternion quan;

			quan.w = f / a.w;
			quan.x = f / a.x;
			quan.y = f / a.y;
			quan.z = f / a.z;

			return quan;
		}

		inline void zero()
		{
			w = 0.0;
			x = 0.0;
			y = 0.0;
			z = 0.0;
		}

		inline void invalid()
		{
			*this = INVALID;
		}

		inline void set(float w, float x, float y, float z)
		{
			this->w = w;
			this->x = x;
			this->y = y;
			this->z = z;
		}

		inline void set(float value)
		{
			this->w = value;
			this->x = value;
			this->y = value;
			this->z = value;
		}

		inline void set(float* p)
		{
			this->w = p[0];
			this->x = p[1];
			this->y = p[2];
			this->z = p[3];
		}

		inline float dot(const Quaternion& rhs) const
		{
			return (w * rhs.w + x * rhs.x + y * rhs.y + z * rhs.z);
		}

		inline Quaternion cross(const Quaternion& rhs)
		{
			Quaternion quan;
			quan.w = w * rhs.w - x * rhs.x - y * rhs.y - z *rhs.z;
			quan.x = w * rhs.x + x * rhs.w + y * rhs.z - z *rhs.y;
			quan.y = w * rhs.y + y * rhs.w + z * rhs.x - x *rhs.z;
			quan.z = w * rhs.z + z * rhs.w + x * rhs.y - y *rhs.x;

			return quan;
		}

		inline void conjugate()
		{
			x = -x;
			y = -y;
			z = -z;
		}

		inline void inverse()
		{
			//conjugate();
			const float norm = lenSqr();

			if(norm == 0.0)
			{
				invalid();
				return;
			}

			float invNorm = 1 / norm;
			x *= -invNorm;
			y *= -invNorm;
			z *= -invNorm;
			w *= invNorm;
		}

		inline Quaternion inversedCopy() const
		{
			Quaternion copy = *this;
			copy.inverse();
			return copy;
		}

		inline float len() const
		{
			float qLen;

			float sum = w * w + x * x + y * y + z * z;
			qLen = Math::Sqrt(sum);

			return qLen;
		}

		inline float lenSqr() const
		{
			return w * w + x * x + y * y + z * z;
		}

		inline void identity()
		{
			w = 1.0;
			x = 0.0;
			y = 0.0;
			z = 0.0;
		}

		inline Quaternion log() const
		{
			float a = Math::ACos(w);
			float sina = Math::Sin(a);

			Quaternion quat;
			quat.w = 0;

			if (sina > 0)
			{
				quat.x = a * x / sina;
				quat.y = a * y / sina;
				quat.z = a * z / sina;
			}
			else
				quat.x = quat.y = quat.z = 0;

			return quat;
		}

		inline Quaternion exp() const
		{
			float a = len();
			float sina = Math::Sin(a);
			float cosa = Math::Cos(a);

			Quaternion quan;
			quan.w = cosa;

			if(a > 0)
			{
				quan.x = sina * x / a;
				quan.y = sina * y / a;
				quan.z = sina * z / a;
			}
			else
				quan.x = quan.y = quan.z = 0;

			return quan;
		}

		inline Quaternion pow(float fExp) const
		{
			if(Math::Abs(w) >= 1.0)
				return *this;

			// alpha = theta / 2
			float alpha = Math::ACos(w);
			float newAlpha = alpha * fExp;

			// calculate w
			Quaternion quan;
			quan.w = Math::Cos(newAlpha);

			// calculate xyz
			float mult = Math::Sin(newAlpha) / Math::Sin(alpha);
			quan.x = x * mult;
			quan.y = y * mult;
			quan.z = z * mult;

			return quan;
		}

		inline void normalize()
		{
			float length = len();
			x /= length;
			y /= length;
			z /= length;
		}

		inline Quaternion normalizedCopy() const
		{
			Quaternion copy = *this;
			copy.normalize();
			return copy;
		}

		inline Matrix4 toMat4() const
		{
			Matrix4 ret;
			toMat4(ret);
			return ret;
		}

		inline void toMat4(Matrix4& mat) const
		{
			float xs = x * 2.0f;
			float ys = y * 2.0f;
			float zs = z * 2.0f;
			float wx = w * xs;
			float wy = w * ys;
			float wz = w * zs;
			float xx = x * xs;
			float xy = x * ys;
			float xz = x * zs;
			float yy = y * ys;
			float yz = y * zs;
			float zz = z * zs;

			mat.m00 = 1.0f - (yy + zz);	mat.m01 = xy + wz;			mat.m02 = xz - wy;			mat.m03 = 0.0f;
			mat.m10 = xy - wz;			mat.m11 = 1.0f - (xx + zz);	mat.m12 = yz + wx;			mat.m13 = 0.0f;
			mat.m20 = xz + wy;			mat.m21 = yz - wx;			mat.m22 = 1.0f - (xx + yy);	mat.m23 = 0.0f;
			mat.m30 = 0.0f;				mat.m31 = 0.0f;				mat.m32 = 0.0f;				mat.m33 = 1.0f;
		}

		inline void fromMat4(const Matrix4& mat)
		{
			mat.decompose(nullptr,this,nullptr);
			/*
			Real fTrace = mat.m00 + mat.m11 + mat.m22;
			Real fRoot;

			if (fTrace > 0.0)
			{
				// |w| > 1/2, may as well choose w > 1/2
				fRoot = Math::Sqrt(fTrace + 1.0f);  // 2w
				w = 0.5f * fRoot;
				fRoot = 0.5f / fRoot;  // 1/(4w)
				x = (mat.m12 - mat.m21) * fRoot;
				y = (mat.m20 - mat.m02) * fRoot;
				z = (mat.m01 - mat.m10) * fRoot;
			}
			else
			{
				// |w| <= 1/2
				static int nNext[3] = {1, 2, 0};
				int i = 0;
				if (mat.m11 > mat.m00)
					i = 1;
				if (mat.m22 > mat(i, i))
					i = 2;
				int j = nNext[i];
				int k = nNext[j];

			//	fRoot = Math::Sqrt(mat(i, i) - mat(j, j) - mat(k, k) + 1.0f);
			//	Real* nQuan[3] = { &x, &y, &z };
			//	*nQuan[i] = 0.5f * fRoot;
			//	fRoot = 0.5f / fRoot;
			//	w = (mat[j][k] - mat[k][j]) * fRoot;
			//	*nQuan[j] = (mat(i, j) + mat(j, i)) * fRoot;
			//	*nQuan[k] = (mat(i, k) + mat(k, i)) * fRoot;
			//}
			*/
		}

		inline void fromVec3ToVec3(const Vector3& from, const Vector3& to)
		{
			Vector3 s = from;
			s.normalize();
			Vector3 t = to;
			t.normalize();

			Vector3 sxt = s.cross(t); // SxT
			float sxtLen = sxt.len(); // == cos(angle)
			float dot = s.dot(t);
			if (Math::IsEqual(sxtLen, 0.0f))
			{
				// parallel case.

				// 04/7/6 added. fix bug.
				if (dot > 0.0)
					*this = IDENTITY;
				else
					// inverse.
					rotateAxis(from.perpendicular(), Math::PI);

				return;
			}

			Vector3 u = sxt / sxtLen;

			float angle2 = Math::ACos(dot)/2.0f;

			float sina = Math::Sin(angle2);
			float cosa = Math::Cos(angle2);

			x = u.x * sina;
			y = u.y * sina;
			z = u.z * sina;
			w = cosa;
		}

		inline static Quaternion FromVec3ToVec3(const Vector3& from, const Vector3& to)
		{
			Quaternion q;
			q.fromVec3ToVec3(from, to);
			return q;
		}

		inline void fromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
		{
			Matrix4 kRot = Matrix4::IDENTITY;
			kRot.m00 = xAxis.x;
			kRot.m01 = xAxis.y;
			kRot.m02 = xAxis.z;

			kRot.m10 = yAxis.x;
			kRot.m11 = yAxis.y;
			kRot.m12 = yAxis.z;

			kRot.m20 = zAxis.x;
			kRot.m21 = zAxis.y;
			kRot.m22 = zAxis.z;

			float fTrace = kRot.m00+kRot.m11+kRot.m22;
			float fRoot;

			if ( fTrace > 0.0 )
			{
				// |w| > 1/2, may as well choose w > 1/2
				fRoot = Math::Sqrt(fTrace + 1.0f);  // 2w
				w = 0.5f*fRoot;
				fRoot = 0.5f/fRoot;  // 1/(4w)
				x = (kRot.m12-kRot.m21)*fRoot;
				y = (kRot.m20-kRot.m02)*fRoot;
				z = (kRot.m01-kRot.m10)*fRoot;
			}
			else
			{
				// |w| <= 1/2
				static unsigned int s_iNext[3] = { 1, 2, 0 };
				unsigned int i = 0;
				if ( kRot.m11 > kRot.m00 )
					i = 1;
				if ( kRot.m22 > kRot[i][i] )
					i = 2;
				unsigned int j = s_iNext[i];
				unsigned int k = s_iNext[j];

				fRoot = Math::Sqrt(kRot[i][i]-kRot[j][j]-kRot[k][k] + 1.0f);
				float* apkQuat[3] = { &x, &y, &z };
				*apkQuat[i] = 0.5f*fRoot;
				fRoot = 0.5f/fRoot;
				w = (kRot[j][k]-kRot[k][j])*fRoot;
				*apkQuat[j] = (kRot[j][i]+kRot[i][j])*fRoot;
				*apkQuat[k] = (kRot[k][i]+kRot[i][k])*fRoot;
			}
		}

		inline void rotateVec3(Vector3& outVec, const Vector3& vec) const
		{
			//Mat4 matRotate = ToMat4();
			//return matRotate.RotateVec3(vec);

			// nVidia SDK implementation
			Vector3 uv, uuv;
			Vector3 qvec(x, y, z);
			uv = qvec.cross(vec);
			uuv = qvec.cross(uv);
			uv *= 2.0f * w;
			uuv *= 2.0f;

			outVec = vec + uv + uuv;
		}

		inline void diff(const Quaternion& q1, const Quaternion& q2)
		{
			Quaternion invQ1 = q1;
			invQ1.inverse();
			*this = invQ1 * q2;
		}

		inline Quaternion& abs()
		{
			x = Math::Abs(x);
			y = Math::Abs(y);
			z = Math::Abs(z);
			w = Math::Abs(w);

			return *this;
		}

		inline Quaternion& neg()
		{
			x = -x;
			y = -y;
			z = -z;
			w = -w;

			return *this;
		}

		inline bool isInvalid() const
		{
			return Math::IsInvalid(w) || Math::IsInvalid(x) || Math::IsInvalid(y) || Math::IsInvalid(z);
		}

		inline Vector3 getAxis() const
		{
			return Vector3(x, y, z);
		}

		inline Vector3 xAxis() const 
		{
			//Real fTx  = 2.0*x;
			float fTy  = 2.0f*y;
			float fTz  = 2.0f*z;
			float fTwy = fTy*w;
			float fTwz = fTz*w;
			float fTxy = fTy*x;
			float fTxz = fTz*x;
			float fTyy = fTy*y;
			float fTzz = fTz*z;

			return Vector3(1.0f-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
		}

		inline Vector3 yAxis() const 
		{
			float fTx  = 2.0f*x;
			float fTy  = 2.0f*y;
			float fTz  = 2.0f*z;
			float fTwx = fTx*w;
			float fTwz = fTz*w;
			float fTxx = fTx*x;
			float fTxy = fTy*x;
			float fTyz = fTz*y;
			float fTzz = fTz*z;

			return Vector3(fTxy-fTwz, 1.0f-(fTxx+fTzz), fTyz+fTwx);
		}

		inline Vector3 zAxis() const
		{
			float fTx  = 2.0f*x;
			float fTy  = 2.0f*y;
			float fTz  = 2.0f*z;
			float fTwx = fTx*w;
			float fTwy = fTy*w;
			float fTxx = fTx*x;
			float fTxz = fTz*x;
			float fTyy = fTy*y;
			float fTyz = fTz*y;

			return Vector3(fTxz+fTwy, fTyz-fTwx, 1.0f-(fTxx+fTyy));
		}

		inline float getRadian() const
		{
			return Math::ACos(w) * 2.0f;
		}

		inline void rotateAxis(const Vector3& axis, float radian)
		{
			// assert:  axis is unit length
			// The quaternion representing the rotation is
			//   q = cos(A / 2) + sin(A / 2 ) * (x * i + y * j + z * k)

			float alpha = 0.5f * radian;
			float sina = Math::Sin(alpha);
			w = Math::Cos(alpha);
			x = sina * axis.x;
			y = sina * axis.y;
			z = sina * axis.z;
		}

		// ZXY extrinsic rotation (equivalent to YXZ, or yaw pitch roll order in instrinsic rotation)
		inline void fromEulerAngle(float pitch, float yaw, float roll)
		{
			float fCosHRoll = Math::Cos(roll * Math::DEG2RAD * 0.5f);
			float fSinHRoll = Math::Sin(roll * Math::DEG2RAD * 0.5f);
			float fCosHPitch = Math::Cos(pitch * Math::DEG2RAD * 0.5f);
			float fSinHPitch = Math::Sin(pitch * Math::DEG2RAD * 0.5f);
			float fCosHYaw = Math::Cos(yaw * Math::DEG2RAD * 0.5f);
			float fSinHYaw = Math::Sin(yaw * Math::DEG2RAD * 0.5f);

			//w = fCosHRoll * fCosHPitch * fCosHYaw + fSinHRoll * fSinHPitch * fSinHYaw;
			//x = fSinHRoll * fCosHPitch * fCosHYaw - fCosHRoll * fSinHPitch * fSinHYaw;
			//y = fCosHRoll * fSinHPitch * fCosHYaw + fSinHRoll * fCosHPitch * fSinHYaw;
			//z = fCosHRoll * fCosHPitch * fSinHYaw - fSinHRoll * fSinHPitch * fCosHYaw;

			w = fCosHRoll * fCosHPitch * fCosHYaw + fSinHRoll * fSinHPitch * fSinHYaw;
			x = fCosHRoll * fSinHPitch * fCosHYaw + fSinHRoll * fCosHPitch * fSinHYaw;
			y = fCosHRoll * fCosHPitch * fSinHYaw - fSinHRoll * fSinHPitch * fCosHYaw;
			z = fSinHRoll * fCosHPitch * fCosHYaw - fCosHRoll * fSinHPitch * fSinHYaw;
		}

		inline static Quaternion FromEulerAngle(float pitch, float yaw, float roll)
		{
			Quaternion q;
			q.fromEulerAngle(pitch, yaw, roll);
			return q;
		}

		// ZXY extrinsic rotation (equivalent to YXZ, or yaw pitch roll order in instrinsic rotation)
		inline void toEulerAngle(float& pitch, float& yaw, float& roll) const
		{
			auto sinPitch = 2.0f * (w * x - y * z);
			constexpr float kGimbalLockThreshold = 0.0001f;
			if (1 - std::abs(sinPitch) < kGimbalLockThreshold)
			{
				// 当pitch接近90度或-90度时，发生万向锁，需要特殊处理。这个时候只要roll + yaw等于一个固定值，
				// roll和yaw可以是任意值。我们不妨将roll设置为0
				roll = 0;
				pitch = sinPitch > 0 ? 90.f : -90.f;
				auto cosYaw = 1 - 2 * (y * y + z * z);
				auto sinYaw = 2 * (w * y - x * z);
				yaw = Math::ATan2(sinYaw, cosYaw) * Math::RAD2DEG;
				return;
			}
			roll = Math::ATan2(2.0f * (w * z + x * y), 1.0f - 2.0f * (z * z + x * x));
			pitch = Math::ASin(2.0f * (w * x - y * z));
			yaw = Math::ATan2(2.0f * (w * y + z * x), 1.0f - 2.0f * (x * x + y * y));

			pitch = pitch * Math::RAD2DEG;
			yaw = yaw * Math::RAD2DEG;
			roll = roll * Math::RAD2DEG;
		}

	public:
		static inline Quaternion Log(const Quaternion& quan)
		{
			float a = Math::ACos(quan.w);
			float sina = Math::Sin(a);

			Quaternion q;
			q.w = 0;

			if (sina > 0)
			{
				q.x = a * quan.x / sina;
				q.y = a * quan.y / sina;
				q.z = a * quan.z / sina;
			}
			else
				q.x = q.y = q.z = 0;

			return q;
		}

		static inline Quaternion Exp(const Quaternion& quan)
		{
			float a = quan.len();
			float sina = Math::Sin(a);
			float cosa = Math::Cos(a);

			Quaternion q;
			q.w = cosa;

			if(a > 0)
			{
				q.x = sina * quan.x / a;
				q.y = sina * quan.y / a;
				q.z = sina * quan.z / a;
			}
			else
				q.x = q.y = q.z = 0;

			return q;
		}

		static Quaternion LookRotation(const Vector3& forward, const Vector3& up);

		static inline Quaternion Pow(const Quaternion& quan, float fExp)
		{
			if(Math::Abs(quan.w) >= 1.0)
				return quan;

			// alpha = theta / 2
			float alpha = Math::ACos(quan.w);
			float newAlpha = alpha * fExp;

			// calculate w
			Quaternion q;
			q.w = Math::Cos(newAlpha);

			// calculate xyz
			float mult = Math::Sin(newAlpha) / Math::Sin(alpha);
			q.x = quan.x * mult;
			q.y = quan.y * mult;
			q.z = quan.z * mult;

			return q;
		}

		/** Performs Normalised linear interpolation between two quaternions, and returns the result.
		Lerp ( 0.0f, A, B ) = A
		Lerp ( 1.0f, A, B ) = B
		@remarks
		Nlerp is faster than Slerp.
		Nlerp has the proprieties of being commutative (@see Slerp;
		commutativity is desired in certain places, like IK animation), and
		being torque-minimal (unless shortestPath=false). However, it's performing
		the interpolation at non-constant velocity; sometimes this is desired,
		sometimes it is not. Having a non-constant velocity can produce a more
		natural rotation feeling without the need of tweaking the weights; however
		if your scene relies on the timing of the rotation or assumes it will point
		at a specific angle at a specific weight value, Slerp is a better choice.
		*/
		static inline void Lerp(Quaternion& quan, const Quaternion& q1, const Quaternion& q2, float t, bool bShortestPath = false)
		{
			t = Math::Clamp(t, 0.0f, 1.0f);
			float fCos = q1.dot(q2);
			if (fCos < 0.0f && bShortestPath)
			{
				quan = q1 + t * ((-q2) - q1);
			}
			else
			{
				quan = q1 + t * (q2 - q1);
			}

			quan.normalize();
		}


		/** Performs Spherical linear interpolation between two quaternions, and returns the result.
		Slerp ( 0.0f, A, B ) = A
		Slerp ( 1.0f, A, B ) = B
		@return Interpolated quaternion
		@remarks
		Slerp has the proprieties of performing the interpolation at constant
		velocity, and being torque-minimal (unless shortestPath=false).
		However, it's NOT commutative, which means
		Slerp ( 0.75f, A, B ) != Slerp ( 0.25f, B, A );
		therefore be careful if your code relies in the order of the operands.
		This is specially important in IK animation.
		*/
		static void		Slerp(Quaternion &quan, const Quaternion &q1, const Quaternion &q2, float t, bool bShortestPath = false);
		static Quaternion Slerp(const Quaternion &q1, const Quaternion &q2, float t, bool bShortestPath = false);

		// spherical quadratic interpolation
		static void		Squad(Quaternion &quan, const Quaternion &q1,const Quaternion &q2, const Quaternion &a, const Quaternion &b, float t, bool bShortestPath = false);

		void			Spline(Quaternion &quan, const Quaternion &q1,const Quaternion &q2, const Quaternion &q3);
	};
}
#include "Matrix4.h"
#include "Quaternion.h"

#define QUAN_EPSILON	(float)(1e-03)

namespace Math
{
	const Quaternion Quaternion::IDENTITY(1, 0, 0, 0);
	const Quaternion Quaternion::INVALID(Math::MAX_FLOAT, Math::MAX_FLOAT, Math::MAX_FLOAT, Math::MAX_FLOAT);
	const Quaternion Quaternion::ZERO(0.f, 0.f, 0.f, 0.f);

	/*
	// This version of slerp, used by squad, does not check for theta > 180.
	Quan QuanSlerpNoInvert(const Quan &q1, const Quan &q2, Real t)
	{
	Real dot = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
	Quan quan;

	if (dot > -0.95f && dot < 0.95f)
	{
	Real angle = Math::ACos(dot);
	Real sina, sinat, sinaomt;
	sina = Math::Sin(angle);
	sinat = Math::Sin(angle * t);
	sinaomt = Math::Sin(angle * (1 - t));
	quan = (q1 * sinaomt + q2 * sinat) / sina;
	}

	//if the angle is small, use linear interpolation
	else
	quan.lerp(q1, q2, t);

	return quan;
	}
	*/

	// Creates a rotation with the specified forward and upwards directions.
	//	 forward: The direction to look in.
	//   upwards: The vector that defines in which direction up is.
	// https://docs.unity3d.com/ScriptReference/Quaternion.LookRotation.html
	// https://answers.unity.com/questions/467614/what-is-the-source-code-of-quaternionlookrotation.html
	Quaternion Quaternion::LookRotation(const Vector3& forward, const Vector3& up)
	{
		auto vector = forward.normalizedCopy();
		auto vector2 = (Vector3::Cross(up, vector)).normalizedCopy();
		auto vector3 = Vector3::Cross(vector, vector2);

		auto m00 = vector2.x;
		auto m01 = vector2.y;
		auto m02 = vector2.z;
		auto m10 = vector3.x;
		auto m11 = vector3.y;
		auto m12 = vector3.z;
		auto m20 = vector.x;
		auto m21 = vector.y;
		auto m22 = vector.z;

		float num8 = (m00 + m11) + m22;
		Quaternion quaternion;
		if (num8 > 0.0f)
		{
			auto num = (float)std::sqrt(num8 + 1.0f);
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;
			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			auto num7 = (float)std::sqrt(((1.0f + m00) - m11) - m22);
			auto num4 = 0.5f / num7;
			quaternion.x = 0.5f * num7;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = (m12 - m21) * num4;
			return quaternion;
		}
		if (m11 > m22)
		{
			auto num6 = (float)std::sqrt(((1.0f + m11) - m00) - m22);
			auto num3 = 0.5f / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;
			return quaternion;
		}
		auto num5 = (float)std::sqrt(((1.0f + m22) - m00) - m11);
		auto num2 = 0.5f / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = (m01 - m10) * num2;
		return quaternion;
	}

	void Quaternion::Slerp(Quaternion& quan, const Quaternion& q1, const Quaternion& q2, float t, bool bShortestPath)
	{
		quan = Slerp(q1, q2, t, bShortestPath);
	}

	Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, float t, bool bShortestPath)
	{
		Quaternion quan;
		float fCos = q1.dot(q2);
		Quaternion q;

		// do we need to invert rotation?
		if (fCos < 0.0f && bShortestPath)
		{
			fCos = -fCos;
			q = -q2;
		}
		else
		{
			q = q2;
		}

		t = Math::Clamp(t, 0.0f, 1.0f);

		if (Math::Abs(fCos) < 1 - QUAN_EPSILON)
		{
			// Standard case (slerp)
			float fSin = Math::Sqrt(1 - Math::Sqr(fCos));
			float radian = Math::ATan2(fSin, fCos);
			float fInvSin = 1.0f / fSin;
			float fCoeff0 = Math::Sin((1.0f - t) * radian) * fInvSin;
			float fCoeff1 = Math::Sin(t * radian) * fInvSin;
			quan = fCoeff0 * q1 + fCoeff1 * q;
		}
		else
		{
			// There are two situations:
			// 1. "q1" and "q2" are very close (fCos ~= +1), so we can do a linear
			//    interpolation safely.
			// 2. "q1" and "q2" are almost inverse of each other (fCos ~= -1), there
			//    are an infinite number of possibilities interpolation. but we haven't
			//    have method to fix this case, so just use linear interpolation here.
			quan = (1.0f - t) * q1 + t * q;
			// taking the complement requires renormalisation
			quan.normalize();
		}
		return quan;
	}

	void Quaternion::Squad(Quaternion& quan, const Quaternion& q1,const Quaternion& q2, const Quaternion& a, const Quaternion& b, float t, bool bShortestPath)
	{
		float slerpT = 2.0f * t * (1.0f - t);
		Quaternion slerpQ1;
		Slerp(slerpQ1, q1, q2, t, bShortestPath);
		Quaternion slerpQ2;
		Slerp(slerpQ2, a, b, t);
		Slerp(quan, slerpQ1 ,slerpQ2, slerpT);
	}

	void Quaternion::Spline(Quaternion& quan, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3)
	{
		Quaternion q;

		q.w = q2.w;
		q.x = -q2.x;
		q.y = -q2.y;
		q.z = -q2.z;

		quan = q2 * Exp((Log(q * q1) + Log(q * q3)) / -4);
	}

}

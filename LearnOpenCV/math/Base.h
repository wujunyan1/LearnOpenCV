#pragma once

#ifndef MATH_BASE_H
#define MATH_BASE_H

#include <stdlib.h>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>

namespace Math {

#define D_PI  double (3.1415926535897932384626433832795)
#define F_PI  3.14159265358979323846f
	static unsigned int nextId = 0;
	static const float PI = F_PI;
	const float LOWEPSILON = (float)(1e-04);
	const float EPSILON = std::numeric_limits<float>::epsilon();

	const float MIN_FLOAT = 1.175494351e-38F;
	const float MAX_FLOAT = 3.402823466e+38F;
	const double MIN_DOUBLE = 2.2250738585072014e-308;
	const double MAX_DOUBLE = 1.7976931348623158e+308;

	const float DEG2RAD = (float)0.01745329;
	const float RAD2DEG = (float)57.29577;

	template <typename T>
	inline T Sqrt(T n) {
		return std::sqrt(n);
	}

	inline float Sin(float r) {
		return std::sin(r);
	}

	inline float Cos(float r) {
		return std::cos(r);
	}

	inline float ASin(float r) {
		return std::asin(r);
	}

	inline float ACos(float r) {
		return std::acos(r);
	}

	// [0, 2*PI]
	template <typename T>
	inline T ATan(const T& x)
	{
		return std::atan(x);
	}

	// [-PI, PI]
	template <typename T>
	inline T ATan2(const T& y, const T& x)
	{
		return std::atan2(y, x);
	}

	template <typename T>
	inline float Max(T l, T r) {
		return std::max(l, r);
	}

	template <typename T>
	inline float Min(T l, T r) {
		return std::min(l, r);
	}

	template <typename T>
	inline T Floor(const T& x)
	{
		return std::floor(x);
	}

	template <typename T>
	inline T Ceil(const T& x)
	{
		return std::ceil(x);
	}


	template <typename T>
	inline T const& Clamp(const T& val, const T& low, const T& high)
	{
		return std::max<T>(low, std::min<T>(high, val));
	}

	template <typename T>
	inline T Sqr(const T& x)
	{
		return x * x;
	}

	template <typename T>
	inline void Swap(T& x, T& y)
	{
		/*
		T temp;
		temp = x;
		x = y;
		y = temp;
		*/

		std::swap(x, y);
	}

	inline float radians(float angle)
	{
		return angle * 0.01745329251994329576923690768489f;
	}

	inline float degrees(float radians)
	{
		return radians * (57.295779513082320876798154814105);
	}

	template <typename T>
	inline T Abs(const T& x)
	{
		return x < T(0) ? -x : x;
	}

	template <typename T>
	inline bool IsEqual(const T& lhs, const T& rhs, const T epsilon = (T)LOWEPSILON)
	{
		return (lhs == rhs);
	}

	template <>
	inline bool IsEqual<float>(const float& lhs, const float& rhs, const float epsilon)
	{
		return std::abs(lhs - rhs) <= epsilon * std::max({ 1.0f, std::abs(lhs), std::abs(rhs) });
	}

	template <>
	inline bool IsEqual<double>(const double& lhs, const double& rhs, const double epsilon)
	{
		return Abs(lhs - rhs) <= epsilon * std::max({ 1.0, std::abs(lhs), std::abs(rhs) });
	}

	inline bool IsInvalid(float f)
	{
		// std::isnan() is C99, not supported by all compilers
		// However NaN always fails this next test, no other number does.
		return f == MAX_FLOAT;
	}

	std::string stringFormat(std::string fmt, ...);

	unsigned int getUid();

	class Vector1;
	class Vector2;
	class Vector3;
	class Vector4;
	class Matrix4;
}

#endif
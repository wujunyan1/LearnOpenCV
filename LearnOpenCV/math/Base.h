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
#define F_PI  = 3.14159265358979323846f;

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

	std::string getUid();

	class Vector1;
	class Vector2;
	class Vector3;
	class Vector4;
	class Matrix4;
}

#endif
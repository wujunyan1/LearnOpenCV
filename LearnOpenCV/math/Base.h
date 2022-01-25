#pragma once

#include <stdlib.h>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>

namespace Math {
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


	class Vector1;
	class Vector2;
	class Vector3;
	class Vector4;
	class Matrix4;
}


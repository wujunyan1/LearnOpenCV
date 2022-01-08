#pragma once

#include <stdlib.h>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

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


	class Vector3;
	class Vector4;
	class Matrix4;
}


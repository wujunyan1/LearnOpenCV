#pragma once

#include <stdlib.h>
#include <cmath>
#include <cstring>

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
}


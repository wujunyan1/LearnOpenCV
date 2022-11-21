#pragma once
#include "Base.h"

namespace Math {
	class Quaternion
	{
	public:
		union
		{
			struct
			{
				float x, y, z, w;
			};
			float m[4];
		};

	public:
		inline Quaternion()
			: x(0.0f)
			, y(0.0f)
			, z(0.0f)
			, w(0.0f) {

		}

	public:
	};
}


#pragma once

#include "../../Core/Core.h"
#include "../../Util/StringUtil.h"
#include "../../math/Math.h"

#include "HexMetrics.h"

using namespace std;
using namespace Core;

namespace War
{
	struct HexCoordinates
	{
	public:
		int X;
		int Z;

		Vector3 position;
	public: 
		HexCoordinates(int x, int z) {
			X = x;
			Z = z;

			position = Vector3();

			position.x = x * 1.5 * HexMetrics::outerRadius;
			position.y = 0.0f;
			position.z = (2 * z + x % 2) * HexMetrics::innerRadius;
		}

		string toString() {
			return Core::StringUtil::Format("(%d, %d)", X, Z);
		}
	};
}
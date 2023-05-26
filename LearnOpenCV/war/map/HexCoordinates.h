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

			position.x = (x + z * 0.5f - z / 2) * (HexMetrics::innerRadius * 2.0f);
			position.y = 0.0f;
			position.z = z * (HexMetrics::outerRadius * 1.5f);
		}

		string toString() {
			return Core::StringUtil::Format("(%d, %d)", X, Z);
		}
	};
}
#pragma once

#include "../../Core/Core.h"

namespace War
{
	static class HexMetrics
	{
	public:
		static const float outerRadius;
		static const float innerRadius;
	};

	const float HexMetrics::outerRadius = 10.0f;
	const float HexMetrics::innerRadius = HexMetrics::outerRadius * 0.866025404f;
}
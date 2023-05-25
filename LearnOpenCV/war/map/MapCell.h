#pragma once

#include "../../Core/Core.h"
#include "../../Core/Component.h"

using namespace Core;

namespace War
{
	enum HexagonDirection
	{

	};

	class MapCell
	{
	public:
		const float radius = 1;
		const float width = radius * 1.732;
		const float height = radius;

	public:
		MapCell();

	private:
		ui16 row;
		ui16 col;

		Vector3 position;

		MapCell* nears[6];
	};
}
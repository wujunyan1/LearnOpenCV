#pragma once

#include "../../Core/Core.h"
#include "../../Core/Component.h"

#include "HexCoordinates.h"

using namespace Core;

namespace War
{
	enum HexDirection
	{
		NE, E, SE, SW, W, NW
	};

	static class HexDirectionExtensions {

	public:
		static HexDirection Opposite(HexDirection direction) {
			return (HexDirection)((int)direction < 3 ? (direction + 3) : (direction - 3));
		}
	};


	class MapCell
	{
	public:

	public:
		MapCell();

		void init(ui16 row, ui16 col);

		void setNear(HexDirection dir, MapCell* cell);
		
		MapCell* GetNeighbor(HexDirection direction) {
			return nears[(int)direction];
		}
	private:
		HexCoordinates corrdinates = HexCoordinates(0, 0);

		MapCell* nears[6];
	};
}
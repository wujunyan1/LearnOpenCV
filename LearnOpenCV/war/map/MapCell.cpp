#include "MapCell.h"

War::MapCell::MapCell()
{
}

void War::MapCell::init(ui16 x, ui16 z)
{
	corrdinates = HexCoordinates(x, z);
}

void War::MapCell::setNear(HexDirection dir, MapCell* cell)
{
	nears[dir] = cell;
	
	HexDirection oppsite = HexDirectionExtensions::Opposite(dir);
	cell->nears[oppsite] = this;
}

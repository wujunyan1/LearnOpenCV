#include "Map.h"

using namespace War;

Map::Map()
{
	cells = vector<MapCell*>();
}

MapCell* Map::createMapCell(int x, int z, int i)
{
	MapCell* cell = new MapCell();
	cell->init(x, z);

	if (x > 0) {
		cell->setNear(HexDirection::W, cells[i - 1]);
	}
	if (z > 0) {
		if ((z & 1) == 0) {
			cell->setNear(HexDirection::SE, cells[i - m_setting.col]);
			if (x > 0) {
				cell->setNear(HexDirection::SW, cells[i - m_setting.col - 1]);
			}
		}
		else {
			cell->setNear(HexDirection::SW, cells[i - m_setting.col]);
			if (x < m_setting.col - 1) {
				cell->setNear(HexDirection::SE, cells[i - m_setting.col + 1]);
			}
		}
	}

	return cell;
}

void Map::initMap(MapSetting& setting)
{
	m_setting = setting;
	cells.clear();
	cells.reserve(setting.row * setting.col);

	for (size_t y = 0; y < setting.row; y++)
	{
		for (size_t x = 0; x < setting.col; x++)
		{
			ui16 i = x + y * setting.col;
			cells[i] = createMapCell(x, y, i);
		}
	}
}

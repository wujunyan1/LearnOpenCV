#include "Map.h"

using namespace War;

Map* Map::instance = nullptr;

Map::Map()
{
	cells = vector<MapCell*>();
}

MapCell* Map::createMapCell(int x, int z, int i)
{
	MapCell* cell = new MapCell();
	cell->init(x, z);
	cell->setMapCellType( (MapCellType)Math::Random(0, 40) );

	if (x > 0) {
		cell->setNear(HexDirection::W, cells[i - 1]);
	}
	if (z > 0) {
		if ((z & 1) == 0) {
			cell->setNear(HexDirection::SE, cells[i - m_setting.width]);
			if (x > 0) {
				cell->setNear(HexDirection::SW, cells[i - m_setting.width - 1]);
			}
		}
		else {
			cell->setNear(HexDirection::SW, cells[i - m_setting.width]);
			if (x < m_setting.width - 1) {
				cell->setNear(HexDirection::SE, cells[i - m_setting.width + 1]);
			}
		}
	}

	return cell;
}

void Map::initMap(MapSetting& setting)
{
	m_setting = setting;
	cells.clear();
	cells.resize(setting.height * setting.width);

	for (size_t y = 0; y < setting.height; y++)
	{
		for (size_t x = 0; x < setting.width; x++)
		{
			ui32 i = x + y * setting.width;
			cells[i] = createMapCell(x, y, i);
		}
	}
}

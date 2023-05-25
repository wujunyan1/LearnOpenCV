#include "Map.h"

War::Map::Map()
{
	cells = vector<vector<MapCell>>();
}

void War::Map::initMap(MapSetting& setting)
{
	cells.clear();
	cells.resize(setting.row);

	for (vector<MapCell>& cellList : cells)
	{
		cellList.resize(setting.col);
	}


}

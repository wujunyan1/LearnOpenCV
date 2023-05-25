#pragma once

#include "../../Core/Core.h"
#include "../../Core/Object.h"

#include <Vector>
#include "MapCell.h"

#include "../../event/Event.h"
#include "../../event/EventDispatcher.h"
#include "../../event/EventCustom.h"

using namespace std;

using namespace Core;

namespace War
{
	struct MapSetting
	{
		ui16 row;
		ui16 col;



	};

	class Map
	{
	public:
		static Map* GetInstance() {
			if (instance == nullptr) {
				instance = new Map();
			}

			return instance;
		}

		static void DestroyInstance() {
			if (instance != nullptr) {
				delete instance;
				instance = nullptr;
			}
		}

		void initMap(MapSetting& setting);

		MapCell* getMapCell(ui16 x, ui16 y)
		{
			return &cells[x][y];
		};
	private:
		Map();

	private:
		static Map* instance;

		vector<vector<MapCell>> cells;
		EventDispatcher* dispatcher = new EventDispatcher();
	};
}
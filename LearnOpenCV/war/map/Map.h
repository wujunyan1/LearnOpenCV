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
			ui16 index = m_setting.col * y + x;
			return cells[index];
		};
	private:
		Map();

		MapCell* createMapCell(int x, int z, int i);

	private:
		static Map* instance;


		/*
		*	y row
			 |
			 |
			 |---------> x col
		
		*/
		vector<MapCell*> cells;

		MapSetting m_setting;

		EventDispatcher* dispatcher = new EventDispatcher();
	};
}
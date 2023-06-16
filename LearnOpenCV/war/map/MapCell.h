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

	enum MapCellType
	{
		greenLand,		//绿地
		grove,			//小树林
		wood,			//树林
		hill,			//山丘
		hillForest,		//山林
		mountain,		//高山
		shallowWater,	//淡水/浅海
		deepWater,		//深水
		sCity,			//小城/无城墙
		city,			//大城/有城墙
		fortress,		//堡垒/巨城墙
		wheatField,		//麦田
		swampForest,	//沼泽林
		swamp,			//沼泽
		grass,			//草地
		shrub,			//灌木
		snowfield,		//雪地
		snowGrove,		//雪小树林
		snowWood,		//雪树林
		snowHill,		//雪山丘
		snowHillForest,	//雪山林
		iceWater,		//冰水
		snowSCity,		//雪城/无城墙
		snowCastle,		//雪城堡
		desert,			//沙漠
		sandStone,		//沙石
		desertHill,		//沙丘
		desertMountain,	//荒山
		oasis,			//绿洲
		desertVillage,	//沙漠村庄
		desertCity,		//沙漠城市
		desertCastle,	//沙漠城堡
		jungle,			//丛林
		mine,			//矿洞
		snowMine,		//雪矿洞
		desertMine,		//沙矿洞
		portL,			//港口左
		portR,			//港口右
		lighthouse,		//灯塔
		guardTower,		//哨塔
		village,		//村庄
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

		void setMapCellType(MapCellType type)
		{
			cellType = type;
		}

		MapCellType getMapCellType()
		{
			return cellType;
		}

		HexCoordinates getCorrdinates()
		{
			return corrdinates;
		}

	private:
		HexCoordinates corrdinates = HexCoordinates(0, 0);

		MapCell* nears[6];

		MapCellType cellType = MapCellType::deepWater;
	};
}
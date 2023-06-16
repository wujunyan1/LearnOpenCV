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
		greenLand,		//�̵�
		grove,			//С����
		wood,			//����
		hill,			//ɽ��
		hillForest,		//ɽ��
		mountain,		//��ɽ
		shallowWater,	//��ˮ/ǳ��
		deepWater,		//��ˮ
		sCity,			//С��/�޳�ǽ
		city,			//���/�г�ǽ
		fortress,		//����/�޳�ǽ
		wheatField,		//����
		swampForest,	//������
		swamp,			//����
		grass,			//�ݵ�
		shrub,			//��ľ
		snowfield,		//ѩ��
		snowGrove,		//ѩС����
		snowWood,		//ѩ����
		snowHill,		//ѩɽ��
		snowHillForest,	//ѩɽ��
		iceWater,		//��ˮ
		snowSCity,		//ѩ��/�޳�ǽ
		snowCastle,		//ѩ�Ǳ�
		desert,			//ɳĮ
		sandStone,		//ɳʯ
		desertHill,		//ɳ��
		desertMountain,	//��ɽ
		oasis,			//����
		desertVillage,	//ɳĮ��ׯ
		desertCity,		//ɳĮ����
		desertCastle,	//ɳĮ�Ǳ�
		jungle,			//����
		mine,			//��
		snowMine,		//ѩ��
		desertMine,		//ɳ��
		portL,			//�ۿ���
		portR,			//�ۿ���
		lighthouse,		//����
		guardTower,		//����
		village,		//��ׯ
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
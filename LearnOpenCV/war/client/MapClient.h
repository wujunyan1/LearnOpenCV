#pragma once

#include "../../Core/Core.h"
#include "../../Core/Component.h"

#include "../../war/map/Map.h"
#include "../../Core/Model.h"

using namespace Core;

namespace Core
{
	class ACustomMesh;
}

namespace War
{
	class MapClient : public Core::GameComponent
	{
	public:

	public:
		virtual void Init();
		virtual void Bind();
		virtual void Update();

		void setMap(Map* map);

	private:
		
		ACustomMesh* getColMapMesh(int col, int rowStartIndex);

	private:
		Image* cellTextureImage;
		ImageCustom* mapDataImage;
		Map* m_map;

		Model* m_model;

		float m_mapScale = 100.0f;
	};
}
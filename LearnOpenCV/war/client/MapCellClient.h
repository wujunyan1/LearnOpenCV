#pragma once

#include "../../Core/Core.h"
#include "../../war/map/MapCell.h"

#include "../../meshModel/AMesh.h"

namespace War
{
	class MapCellClient
	{
	public:
		static void createMapCellObject(
			MapCell* cell,
			std::vector<AMesh::Vertex>& vertices,
			std::vector<unsigned int>& indices,
			std::vector<Render::Texture>& textures
		);

	};
}
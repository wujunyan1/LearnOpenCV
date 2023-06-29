#pragma once

#include "../../Core/Core.h"
#include "../../war/map/MapCell.h"

#include "../../meshModel/AMesh.h"

namespace War
{
	class MapCellClient
	{
	public:
		struct Vertex
		{
			// position
			Math::Vector3 Position;
			// texCoords
			Math::Vector2 TexCoords;
			// cell position
			Math::Vector3 CellPosition;
		};

		struct InstanceData
		{
			// texCoords
			Math::Vector2T<int> CellCoords;
			// texCoords
			Math::Vector2 CellPosition;
		};

	public:
		static void createMapCellObject(
			MapCell* cell,
			std::vector<Vertex>& vertices,
			std::vector<unsigned int>& indices,
			std::vector<Render::Texture>& textures
		);

	};
}
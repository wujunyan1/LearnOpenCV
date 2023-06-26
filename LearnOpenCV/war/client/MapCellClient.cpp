#include "MapCellClient.h"
#include "../../Core/GameObject.h"
#include "../../Core/Model.h"

#include "../../Core/ObjectManager.h"

using namespace Core;

void War::MapCellClient::createMapCellObject(
	MapCell* cell,
	std::vector<Vertex>& vertices,
	std::vector<unsigned int>& indices,
	std::vector<Render::Texture>& textures
)
{
	unsigned int count = vertices.size();
	printf("count = %u \n", count);

	War::HexCoordinates Corrdinates = cell->getCorrdinates();
	Vector3 position = Corrdinates.position;
	printf("position = %s \n", position.toString().c_str());
	Vector3 cellPosition = Vector3(Corrdinates.X, Corrdinates.Z, 0);

	Vertex vertex1;
	vertex1.Position = position + Math::Vector3(0, 0, -HexMetrics::innerRadius);
	vertex1.TexCoords = Math::Vector2(0, 0);
	vertex1.CellPosition = cellPosition;
	vertices.push_back(vertex1);

	Vertex vertex2;
	vertex2.Position = position + Math::Vector3(2 * HexMetrics::outerRadius, 0, -HexMetrics::innerRadius);
	vertex2.TexCoords = Math::Vector2(1, 0);
	vertex1.CellPosition = cellPosition;
	vertices.push_back(vertex2);

	Vertex vertex3;
	vertex3.Position = position + Math::Vector3(0, 0, 48.0f - HexMetrics::innerRadius);
	vertex3.TexCoords = Math::Vector2(0, 1);
	vertex1.CellPosition = cellPosition;
	vertices.push_back(vertex3);

	Vertex vertex4;
	vertex4.Position = position + Math::Vector3(2 * HexMetrics::outerRadius, 0, 48.0f - HexMetrics::innerRadius);
	vertex4.TexCoords = Math::Vector2(1, 1);
	vertex1.CellPosition = cellPosition;
	vertices.push_back(vertex4);

	indices.push_back(count + 0);
	indices.push_back(count + 1);
	indices.push_back(count + 2);
	indices.push_back(count + 2);
	indices.push_back(count + 1);
	indices.push_back(count + 3);

	// TextureFromFile(str.C_Str(), this->directory);

}

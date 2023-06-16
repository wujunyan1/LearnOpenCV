#include "MapCellClient.h"
#include "../../Core/GameObject.h"
#include "../../Core/Model.h"

#include "../../Core/ObjectManager.h"

using namespace Core;

void War::MapCellClient::createMapCellObject(
	MapCell* cell,
	std::vector<AMesh::Vertex>& vertices,
	std::vector<unsigned int>& indices,
	std::vector<Render::Texture>& textures
)
{
	Vector3 position = cell->getCorrdinates().position;

	AMesh::Vertex vertex1;
	vertex1.Position = position + Math::Vector3(-16.0f, 0, -12.0f);
	vertex1.TexCoords = Math::Vector2(0, 0);
	vertices.push_back(vertex1);

	AMesh::Vertex vertex2;
	vertex2.Position = position + Math::Vector3(16.0f, 0, -12.0f);
	vertex2.TexCoords = Math::Vector2(1, 0);
	vertices.push_back(vertex2);

	AMesh::Vertex vertex3;
	vertex3.Position = Math::Vector3(-16.0f, 0, 12.0f);
	vertex3.TexCoords = Math::Vector2(0, 1);
	vertices.push_back(vertex3);

	AMesh::Vertex vertex4;
	vertex4.Position = Math::Vector3(16.0f, 0, 12.0f);
	vertex4.TexCoords = Math::Vector2(1, 1);
	vertices.push_back(vertex4);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);

	// TextureFromFile(str.C_Str(), this->directory);

	String imagePath = StringUtil::Format("/asserts/map/fantasyhextiles_v3.png:%d", cell->getMapCellType());
	Render::Texture texture;
	texture.image = ImageLoad::GetImage(imagePath);
	texture.imageName = "imagePath";
	texture.uniformName = "diffuse";
	textures.push_back(texture);

}

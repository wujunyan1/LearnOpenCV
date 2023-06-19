#include "MapClient.h"
#include "../../Core/GameObject.h"
#include "../../Core/Model.h"
#include "../../file/ImageLoad.h"

#include "../../meshModel/ACustomMesh.h"

#include "MapCellClient.h"

using namespace Core;

void War::MapClient::Init()
{
}

void War::MapClient::Bind()
{
	GameObject* object = getGameObject();
	m_model = object->GetComponent<Model>();
}

void War::MapClient::setMap(Map* map)
{
	m_map = map;

	ImageLoad::LoadImageAtlas("/asserts/map/fantasyhextiles_v3.png", 32, 48);

	std::vector<MapCellClient::Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Render::Texture> textures;

	MapSetting setting = map->getMapSetting();

	for (size_t i = 0; i < setting.col; i++)
	{
		for (size_t j = 0; j < setting.row; j++)
		{
			MapCell* cell = map->getMapCell(i, j);
			MapCellClient::createMapCellObject(cell, vertices, indices, textures);
		}
	}

	//MapCellClient::createMapCellObject();

	Core::AModel* acustommodel = AModelFactory::createCustomModel();

	ACustomMesh* customMesh = new ACustomMesh("map");

	customMesh->BindArrayBufferData(indices.size(), vertices.size() * sizeof(MapCellClient::Vertex), &vertices[0]);
	customMesh->BindElementBufferData(indices);
	customMesh->VertexAttribPointer(0, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(MapCellClient::Vertex), offsetof(MapCellClient::Vertex, Position));
	customMesh->VertexAttribPointer(1, 2, Render::ShaderParamType::SPT_VEC2, false, sizeof(MapCellClient::Vertex), offsetof(MapCellClient::Vertex, TexCoords));
	customMesh->VertexAttribPointer(2, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(MapCellClient::Vertex), offsetof(MapCellClient::Vertex, CellPosition));

	acustommodel->addBaseMesh(customMesh);

	m_model->setShader("warMapShader");  //testBlendShader
	m_model->setRenderQueue("DefaultRenderQueue");
	m_model->setModel(acustommodel);
	m_model->setDepthTest(false);
	m_model->setBlend(true);
	m_model->setBlendFunc(Render::BlendFunc::SRC_ALPHA, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);
}

#include "MapClient.h"
#include "../../Core/GameObject.h"
#include "../../Core/Model.h"
#include "../../file/ImageLoad.h"

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

	std::vector<AMesh::Vertex> vertices;
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
	acustommodel->addMesh(vertices, indices, textures);

	m_model->setShader("warMapShader");  //testBlendShader
	m_model->setRenderQueue("DefaultRenderQueue");
	m_model->setModel(acustommodel);
	m_model->setDepthTest(false);
	m_model->setBlend(true);
	m_model->setBlendFunc(Render::BlendFunc::SRC_ALPHA, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);
}

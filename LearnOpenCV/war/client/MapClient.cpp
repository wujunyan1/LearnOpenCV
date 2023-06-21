#include "MapClient.h"
#include "../../Core/GameObject.h"
#include "../../Core/Model.h"
#include "../../file/ImageLoad.h"

#include "../../meshModel/ACustomMesh.h"
#include "../../render/Material.h"

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

	Image* cellTextureImage = ImageLoad::LoadImageAtlas("/asserts/map/fantasyhextiles_v3.png", 32, 48);

	std::vector<MapCellClient::Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Render::Texture> textures;

	MapSetting setting = map->getMapSetting();
	ImageCustom* mapDataImage = ImageLoad::CreateCustomImage("warMapData", setting.col, setting.row);

	for (size_t i = 0; i < setting.col; i++)
	{
		for (size_t j = 0; j < setting.row; j++)
		{
			MapCell* cell = map->getMapCell(i, j);
			MapCellClient::createMapCellObject(cell, vertices, indices, textures);

			Vector4 cellData = Vector4(0, 0, 0, cell->getMapCellType() / 255.0);
			mapDataImage->setTextureData(i, j, 1, 1, &cellData);
		}
	}

	Render::Texture mapTexture;
	mapTexture.image = cellTextureImage;
	mapTexture.imageName = "mapTexture";
	mapTexture.uniformName = "mapTexture";
	textures.push_back(mapTexture);


	Render::Texture mapDataTexture;
	mapDataTexture.image = mapDataImage;
	mapDataTexture.imageName = "cellDatas";
	mapDataTexture.uniformName = "cellDatas";
	textures.push_back(mapDataTexture);

	//MapCellClient::createMapCellObject();

	Core::AModel* acustommodel = AModelFactory::createCustomModel();

	ACustomMesh* customMesh = new ACustomMesh("map");

	customMesh->BindArrayBufferData(indices.size(), vertices.size() * sizeof(MapCellClient::Vertex), &vertices[0]);
	customMesh->BindElementBufferData(indices);
	customMesh->VertexAttribPointer(0, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(MapCellClient::Vertex), offsetof(MapCellClient::Vertex, Position));
	customMesh->VertexAttribPointer(1, 2, Render::ShaderParamType::SPT_VEC2, false, sizeof(MapCellClient::Vertex), offsetof(MapCellClient::Vertex, TexCoords));
	customMesh->VertexAttribPointer(2, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(MapCellClient::Vertex), offsetof(MapCellClient::Vertex, CellPosition));
	customMesh->setImage(textures);

	acustommodel->addBaseMesh(customMesh);

	m_model->setShader("warMapShader");  //testBlendShader
	m_model->setRenderQueue("RenderWarMapQueue");
	m_model->setModel(acustommodel);
	m_model->setDepthTest(true);
	m_model->setBlend(false);
	//m_model->setBlendFunc(Render::BlendFunc::SRC_ALPHA, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);

	Render::RenderProgram* program = m_model->getRenderProgram();

	float texCoords[96];
	//Vector2 texCoords[48];
	int width = cellTextureImage->getWidth();
	int height = cellTextureImage->getHeight();

	int col = width / 32;
	int row = height / 48;

	int index = 0;
	for (size_t i = 0; i < col; i++)
	{
		for (size_t j = 0; j < row; j++)
		{
			//texCoords[index++] = { i * 32.0f / width, j * 48.0f / height };
			texCoords[index++] = i * 32.0f / width;
			texCoords[index++] = j * 48.0f / height;
		}
	}

	Render::Material* material = program->getMaterial();
	material->setVec2Array("textureCoords", 48, texCoords);
	material->setVec2("cellSize", 32.0f / width, 48.0f / row );

	/*GLShader* shader = program->getShaderProgram()->GetShaderObj();
	shader->use();
	shader->setVec2Array("textureCoords", 48, texCoords);
	shader->setVec2("cellSize", { 32.0f / width, 48.0f / row });*/
}

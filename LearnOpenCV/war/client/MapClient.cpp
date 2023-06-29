#include "MapClient.h"
#include "../../Core/GameObject.h"
#include "../../Core/Model.h"
#include "../../file/ImageLoad.h"

#include "../../meshModel/AWarMapMesh.h"
#include "../../render/Material.h"
#include "../../render/RenderMain.h"

#include "MapCellClient.h"
#include "../../input/Input.h"

using namespace Core;

void War::MapClient::Init()
{
	m_mapScale = 400.0f;
}

void War::MapClient::Bind()
{
	GameObject* object = getGameObject();
	m_model = object->GetComponent<Model>();
}

void War::MapClient::Update()
{
	Vector2 scrollPos = Core::Input::GetMouseScrollPos();

	float oldMapScale = m_mapScale;
	m_mapScale += scrollPos.y;
	m_mapScale = Math::Min(m_mapScale, 1000.0f);
	m_mapScale = Math::Max(m_mapScale, 1.0f);

	if (!Math::IsEqual(oldMapScale, m_mapScale, 0.01f))
	{
		Render::RenderProgram* program = m_model->getRenderProgram();
		Render::Material* material = program->getMaterial();
		material->setFloat("mapScale", m_mapScale / 100.0f);
	}
}

void War::MapClient::setMap(Map* map)
{
	m_map = map;

	cellTextureImage = ImageLoad::LoadImageAtlas("/asserts/map/fantasyhextiles_v3.png", 32, 48);

	MapSetting setting = map->getMapSetting();
	mapDataImage = ImageLoad::CreateCustomImage("warMapData", setting.width, setting.height);


	Core::AModel* acustommodel = AModelFactory::createCustomModel();
	initCustomRenderMesh(acustommodel);

	m_model->setShader("warMapShader");  //testBlendShader
	m_model->setRenderQueue("RenderWarMapQueue");
	m_model->setModel(acustommodel);
	m_model->setDepthTest(true);
	m_model->setBlend(true);
	m_model->setBlendFunc(Render::BlendFunc::SRC_ALPHA, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);

	Render::RenderProgram* program = m_model->getRenderProgram();

	float texCoords[96];
	//Vector2 texCoords[48];
	int width = cellTextureImage->getWidth();
	int height = cellTextureImage->getHeight();

	int col = width / 32;
	int row = height / 48;

	int index = 0;
	for (int j = row - 1; j >= 0; j--)
	{
		for (size_t i = 0; i < col; i++)
		{
			//texCoords[index++] = { i * 32.0f / width, j * 48.0f / height };
			texCoords[index++] = i * 32.0f / width;
			texCoords[index++] = (j * 48.0f - 2.0f) / height;
			//texCoords[index++] = Math::Max((j * 48.0f - 2.0f) / height, 0.0f);
		}
	}

	Render::Material* material = program->getMaterial();
	material->setFloat("mapScale", m_mapScale / 100.0f);
	material->setVec2Array("textureCoords", 48, texCoords);
	material->setVec2("cellSize", 32.0f / width, 48.0f / height);

	MapCell* maxCell = map->getMapCell(setting.width - 1, setting.height - 1);
	War::HexCoordinates coord = maxCell->getCorrdinates();
	Vector3 pos = coord.position;
	material->setVec2("mapSize", pos.x + HexMetrics::outerRadius, pos.z + 48.0f);

	Render::Texture mapTexture;
	mapTexture.image = cellTextureImage;
	mapTexture.imageName = "mapTexture";
	mapTexture.uniformName = "mapTexture";
	material->setTexture("mapTexture", mapTexture);


	Render::Texture mapDataTexture;
	mapDataTexture.image = mapDataImage;
	mapDataTexture.imageName = "cellDatas";
	mapDataTexture.uniformName = "cellDatas";
	material->setTexture("cellDatas", mapDataTexture);

	/*GLShader* shader = program->getShaderProgram()->GetShaderObj();
	shader->use();
	shader->setVec2Array("textureCoords", 48, texCoords);
	shader->setVec2("cellSize", { 32.0f / width, 48.0f / row });*/
}

void War::MapClient::initCustomRenderMesh(Core::AModel* acustommodel)
{
	if (customRenderMesh)
	{
		delete customRenderMesh;
	}

	customRenderMesh = Render::CreateRenderCustomMesh();

	std::vector<MapCellClient::Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Render::Texture> textures;

	MapSetting setting = m_map->getMapSetting();

	Vector4* meshData = new Vector4[setting.height * 2];

	for (size_t j = 0; j < setting.width; j += 2)
	{
		MapCell* cell = m_map->getMapCell(j, 0);
		MapCellClient::createMapCellObject(cell, vertices, indices, textures);
	}


	AWarMapMesh* customMesh = new AWarMapMesh("map");
	customMesh->SetRenderMesh(customRenderMesh);
	acustommodel->addBaseMesh(customMesh);

	int meshDataIndex = 0;
	for (int i = setting.height - 1; i >= 0; i--)
	{
		for (size_t j = 0; j < setting.width; j++)
		{
			MapCell* cell = m_map->getMapCell(j, i);

			//Vector4 cellData = Vector4(1.0f, 0, 0, 1.0f); // cell->getMapCellType()
			unsigned char cellData[4] = { 255, 0, 0, cell->getMapCellType() };
			mapDataImage->setTextureData(j, i, 1, 1, cellData);
		}

		MapCell* startCell = m_map->getMapCell(1, i);
		War::HexCoordinates Corrdinates = startCell->getCorrdinates();
		Vector3 position1 = Corrdinates.position;
		meshData[meshDataIndex++] = { 1, 1.0f * i, position1.x, position1.z };


		//AWarMapMesh* customMesh2 = getColMapMesh(i, 0);

		startCell = m_map->getMapCell(0, i);
		Corrdinates = startCell->getCorrdinates();
		Vector3 position0 = Corrdinates.position;
		meshData[meshDataIndex++] = { 0, 1.0f * i, position0.x, position0.z };
		//acustommodel->addBaseMesh(customMesh2);
	}

	//MapCellClient::createMapCellObject();

	customRenderMesh->BindArrayBufferData(indices.size(), vertices.size() * sizeof(MapCellClient::Vertex), &vertices[0]);
	customRenderMesh->BindElementBufferData(indices.size() * sizeof(unsigned int), &indices[0]);
	customRenderMesh->VertexAttribPointer(0, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(MapCellClient::Vertex), offsetof(MapCellClient::Vertex, Position));
	customRenderMesh->VertexAttribPointer(1, 2, Render::ShaderParamType::SPT_VEC2, false, sizeof(MapCellClient::Vertex), offsetof(MapCellClient::Vertex, TexCoords));
	customRenderMesh->VertexAttribPointer(2, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(MapCellClient::Vertex), offsetof(MapCellClient::Vertex, CellPosition));
	customRenderMesh->SetImage(textures);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, setting.height * 2 * sizeof(Vector4), &meshData[0], GL_STATIC_DRAW);

	customRenderMesh->VertexAttribDivisor(3, 4, Render::ShaderParamType::SPT_VEC4, false, sizeof(Vector4), 0, 1);
}

AWarMapMesh* War::MapClient::getColMapMesh(int row, int rowStartIndex)
{
	MapSetting setting = m_map->getMapSetting();

	AWarMapMesh* customMesh = new AWarMapMesh("map");
	customMesh->SetRenderMesh(customRenderMesh);

	for (size_t j = 0; j < setting.width; j++)
	{
		MapCell* cell = m_map->getMapCell(j, row);

		//Vector4 cellData = Vector4(1.0f, 0, 0, 1.0f); // cell->getMapCellType()
		unsigned char cellData[4] = { 255, 0, 0, cell->getMapCellType() };
		mapDataImage->setTextureData(j, row, 1, 1, cellData);
	}

	return customMesh;
}

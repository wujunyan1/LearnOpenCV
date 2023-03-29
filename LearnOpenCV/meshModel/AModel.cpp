#include "AModel.h"

using namespace Core;

AModel::AModel()
{
	modelId = Math::getUid();
	gammaCorrection = false;
}

Core::AModel::~AModel()
{
	for (auto it : meshes)
	{
		ABaseMesh* mesh = it;
		delete mesh;
	}

	meshes.clear();
}

AMesh* Core::AModel::addMesh(std::vector<AMesh::Vertex> vertices, std::vector<unsigned int> indices, std::vector<Render::Texture> textures)
{
	return (AMesh*)addMesh(Math::stringFormat("%d|%d", modelId, meshes.size()), vertices, indices, textures);
}

ABaseMesh* Core::AModel::addMesh(std::string name, std::vector<AMesh::Vertex> vertices, std::vector<unsigned int> indices, std::vector<Render::Texture> textures)
{
	AMesh* mesh = new AMesh(name, vertices, indices, textures);
	meshes.push_back(mesh);

	updateObb();
	return mesh;
}

AUIMesh* Core::AModel::createNewUIMesh()
{
	return nullptr;
}

AUIMesh* Core::AModel::addBaseUIMesh(std::string name)
{
	AUIMesh* mesh = AUIMesh::getBaseAUIMesh(name);
	mesh = mesh->clone();
	meshes.push_back(mesh);
	return mesh;
}

void Core::AModel::updateObb()
{
	std::vector<Math::Vector3> points;

	std::vector<Core::ABaseMesh*> ameshs = getMeshs();

	for (size_t i = 0; i < ameshs.size(); i++)
	{
		Core::ABaseMesh* mesh = ameshs[i];
		if (mesh->getMeshType() == AMesh::MeshType)
		{
			Core::AMesh& amesh = (Core::AMesh&)mesh;
			for (size_t j = 0; j < amesh.vertices.size(); j++)
			{
				Core::AMesh::Vertex& vertice = amesh.vertices[j];
				points.push_back(vertice.Position);
			}
		}
	}

	obb.initPoints(points);
}

std::map<std::string, AModel*>* AModelFactory::models = new std::map<std::string, AModel*>();

AModel* AModelFactory::createModel(std::string path)
{
	auto it = models->find(path);
	if (it != models->end())
	{
		return it->second;
	}

	AModel* model = new AModel(path);
	models->insert(std::pair<std::string, AModel*>(path, model));
	return model;
}

AModel* Core::AModelFactory::createCustomModel()
{
	return new AModel();
}

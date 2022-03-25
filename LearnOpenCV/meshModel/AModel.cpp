#include "AModel.h"

using namespace Core;

AModel::AModel()
{
	modelId = Math::getUid();
	gammaCorrection = false;

}

void Core::AModel::addMesh(std::vector<AMesh::Vertex> vertices, std::vector<unsigned int> indices, std::vector<Render::Texture> textures)
{
	meshes.push_back(AMesh(Math::stringFormat("%d|%d", modelId, meshes.size()), vertices, indices, textures));
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

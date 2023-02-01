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

	updateObb();
}

void Core::AModel::updateObb()
{
	std::vector<Math::Vector3> points;

	std::vector<Core::AMesh>& ameshs = getMeshs();

	for (size_t i = 0; i < ameshs.size(); i++)
	{
		Core::AMesh& mesh = ameshs[i];
		for (size_t j = 0; j < mesh.vertices.size(); j++)
		{
			Core::AMesh::Vertex& vertice = mesh.vertices[j];
			points.push_back(vertice.Position);
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

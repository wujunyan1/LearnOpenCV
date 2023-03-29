#include "RenderMesh.h"
#include "../render/Material.h"

namespace Render
{
	std::map<std::string, RenderMesh*>* RenderMesh::meshs = new std::map<std::string, RenderMesh*>();

	RenderMesh* RenderMesh::createNewRenderMesh(std::string& meshName)
	{
		auto it = meshs->find(meshName);
		if (it != meshs->end())
		{
			return it->second;
		}

		RenderMesh* mesh = new RenderMesh(meshName);
		meshs->insert(std::make_pair(meshName, mesh));

		return mesh;
	}

	RenderMesh* RenderMesh::getRenderMesh(std::string& meshName)
	{
		auto it = meshs->find(meshName);
		if (it != meshs->end())
		{
			return it->second;
		}

		return NULL;
	}

	void RenderMesh::addRenderMesh(std::string& meshName, RenderMesh* mesh)
	{
		meshs->insert(std::make_pair(meshName, mesh));
	}

	RenderMesh* RenderMesh::loadMeshFile(std::string& meshName, std::string& path)
	{
		return NULL;
	}
}
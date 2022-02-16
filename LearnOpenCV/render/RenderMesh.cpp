#include "RenderMesh.h"

namespace Render
{
	std::map<std::string, RenderMesh*>* RenderMeshManager::meshs = new std::map<std::string, RenderMesh*>();

	RenderMesh::RenderMesh(std::string _name)
	{
		name = _name;
	}

	RenderMesh::RenderMesh(std::string _name, void* data)
	{
		name = _name;
	}

	void RenderMesh::BindArrayBufferData(size_t dataSize, void* data)
	{
	}

	void RenderMesh::VertexAttribPointer(unsigned int passageway, size_t dataSize, ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
	{
	}


	RenderMesh* RenderMeshManager::createNewRenderMesh(std::string meshName)
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

	RenderMesh* RenderMeshManager::getRenderMesh(std::string meshName)
	{
		return NULL;
	}

	void RenderMeshManager::addRenderMesh(std::string meshName, RenderMesh* mesh)
	{

	}

	void RenderMeshManager::loadMeshFile(std::string meshName, std::string path)
	{

	}
}
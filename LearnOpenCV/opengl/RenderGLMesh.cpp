#include "RenderGLMesh.h"

namespace OpenGL
{
	RenderGLMesh::RenderGLMesh(std::string name) : Render::RenderMesh(name)
	{
		glGenVertexArrays(1, &tvao);
		glGenBuffers(1, &vbo);
	}
	RenderGLMesh::~RenderGLMesh()
	{
	}
	void RenderGLMesh::BindArrayBufferData(size_t dataSize, void* data)
	{
		
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void RenderGLMesh::VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(passageway, dataSize, GL_FLOAT, GL_FALSE, delaySize, (void*)startIndex);
		glEnableVertexAttribArray(passageway);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	std::map<std::string, RenderGLMesh*>* RenderGLMeshManager::meshs = new std::map<std::string, RenderGLMesh*>();

	RenderGLMesh* RenderGLMeshManager::createNewRenderMesh(std::string meshName)
	{
		auto it = meshs->find(meshName);
		if (it != meshs->end())
		{
			return it->second;
		}

		RenderGLMesh* mesh = new RenderGLMesh(meshName);
		meshs->insert(std::make_pair(meshName, mesh));

		return mesh;
	}

	RenderGLMesh* RenderGLMeshManager::getRenderMesh(std::string meshName)
	{
		auto it = meshs->find(meshName);
		if (it != meshs->end())
		{
			return it->second;
		}

		return NULL;
	}

	void RenderGLMeshManager::addRenderMesh(std::string meshName, RenderGLMesh* mesh)
	{
		meshs->insert(std::make_pair(meshName, mesh));
	}

	RenderGLMesh* RenderGLMeshManager::loadMeshFile(std::string meshName, std::string path)
	{
		return NULL;
	}
}
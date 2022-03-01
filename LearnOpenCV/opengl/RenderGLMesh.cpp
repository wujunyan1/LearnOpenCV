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
	void RenderGLMesh::BindArrayBufferData(size_t verticesNum, size_t dataSize, void* data)
	{
		glBindVertexArray(tvao);

		this->verticesNum = verticesNum;
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		/*glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(float), data, GL_STATIC_DRAW);*/

		/*float* vs = new float[9];
		vs[0] = 0.2f;
		vs[1] = 0.0f;
		vs[2] = 0.0f;
		vs[3] = 0.3f;
		vs[4] = 0.2f;
		vs[5] = 0.0f;
		vs[6] = 0.0f;
		vs[7] = 0.0f;
		vs[8] = 0.0f;

		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vs, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);*/
	}
	void RenderGLMesh::VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
	{
		//glBindVertexArray(tvao);
		//glBindBuffer(GL_ARRAY_BUFFER, vbo);
		///*glVertexAttribPointer(passageway, dataSize, GL_FLOAT, GL_FALSE, delaySize, (void*)startIndex);
		//glEnableVertexAttribArray(passageway);*/

		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		

		glGenVertexArrays(1, &tvao);
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		float* vs = new float[9];
		vs[0] = 0.2f;
		vs[1] = 0.0f;
		vs[2] = 0.0f;
		vs[3] = 0.3f;
		vs[4] = 0.2f;
		vs[5] = 0.0f;
		vs[6] = 0.0f;
		vs[7] = 0.0f;
		vs[8] = 0.0f;

		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vs, GL_STATIC_DRAW);

		glBindVertexArray(tvao);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void RenderGLMesh::Render()
	{
		

		glBindVertexArray(tvao);
		glDrawArrays(GL_TRIANGLES, 0, 1);
		glBindVertexArray(0);
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
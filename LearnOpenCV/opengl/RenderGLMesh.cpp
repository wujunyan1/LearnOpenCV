#include "RenderGLMesh.h"

namespace OpenGL
{
	RenderGLMesh::RenderGLMesh(std::string name) : Render::RenderMesh(name)
	{
		glGenVertexArrays(1, &tvao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
	}

	RenderGLMesh::~RenderGLMesh()
	{
	}

	void RenderGLMesh::BindArrayBufferData(size_t verticesNum, size_t dataSize, void* data)
	{
		glBindVertexArray(tvao);
		this->verticesNum = verticesNum;
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	}
	void RenderGLMesh::VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
	{
		glBindVertexArray(tvao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		GLboolean bl = b ? GL_TRUE : GL_FALSE;
		glEnableVertexAttribArray(passageway);
		glVertexAttribPointer(passageway, dataSize, GET_OPENGL_TYPE(dataType), bl, delaySize, (void*)startIndex);


		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		

		/*glGenVertexArrays(1, &tvao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(tvao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		float vertices[] = {
		-0.1f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
			};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);*/
	}

	void RenderGLMesh::BindElementBufferData(size_t dataSize, void* data)
	{
		glBindVertexArray(tvao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	}

	void RenderGLMesh::Render()
	{
		glBindVertexArray(tvao);
		
		for (unsigned int i = 0; i < images.size(); i++)
		{
			images[i]->use(i);
		}

		glDrawElements(GL_TRIANGLES, verticesNum, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}


	std::map<std::string, RenderGLMesh*>* RenderGLMeshManager::meshs = new std::map<std::string, RenderGLMesh*>();

	RenderGLMesh* RenderGLMeshManager::createNewRenderMesh(std::string& meshName)
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
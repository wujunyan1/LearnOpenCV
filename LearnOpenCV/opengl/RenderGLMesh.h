#pragma once

#include "OpenGLCore.h"
#include "../render/RenderMesh.h"

namespace OpenGL
{
	class RenderGLMesh: public Render::RenderMesh
	{
	public:
		RenderGLMesh(std::string name);
		~RenderGLMesh();


		void BindArrayBufferData(size_t verticesNum, size_t dataSize, void* data);
		void VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex);
	
		void Render();
	private:
		unsigned int tvao;
		unsigned int verticesNum;
	};


	class RenderGLMeshManager
	{
	public:
		static RenderGLMesh* createNewRenderMesh(std::string& meshName);
		static RenderGLMesh* getRenderMesh(std::string meshName);
		static void addRenderMesh(std::string meshName, RenderGLMesh* mesh);
		static RenderGLMesh* loadMeshFile(std::string meshName, std::string path);

	private:
		static std::map<std::string, RenderGLMesh*>* meshs;
	};
}
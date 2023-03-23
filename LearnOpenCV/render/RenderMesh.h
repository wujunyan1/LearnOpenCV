#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "../file/Image.h"
#include "Texture.h"
#include "../opengl/OpenGLCore.h"
#include "../opengl/GLShader.h"
#include "../render/Material.h"

namespace Render
{
	/*
		mesh 数据，对应一个vbo
		顶点，uv，光照贴图 等等
	*/
	class RenderMesh
	{
	public:
		RenderMesh(std::string name);
		~RenderMesh();


		void BindArrayBufferData(size_t verticesNum, size_t dataSize, void* data);
		void VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex);
		void BindElementBufferData(size_t dataSize, void* data);

		void SetImage(std::vector<Render::Texture>& images)
		{
			this->images = images;
		};
		void BindRender(GLShader* shader);

		void Render(Render::ShaderProgram* program, Render::Material* material);
	private:
		unsigned int ebo;
		unsigned int vbo;
		unsigned int tvao;
		unsigned int verticesNum;
		std::vector<Render::Texture> images;

		std::string m_name;
	};

	class RenderMeshManager
	{
	public:
		static RenderMesh* createNewRenderMesh(std::string& meshName);
		static RenderMesh* getRenderMesh(std::string& meshName);
		static void addRenderMesh(std::string& meshName, RenderMesh* mesh);
		static RenderMesh* loadMeshFile(std::string& meshName, std::string& path);

	private:
		static std::map<std::string, RenderMesh*>* meshs;
	};

}
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
	class RenderBaseMesh
	{
	public:
		RenderBaseMesh(std::string name);
		~RenderBaseMesh();


		virtual void BindArrayBufferData(size_t verticesNum, size_t dataSize, void* data);
		virtual void VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex);
		virtual void BindElementBufferData(size_t dataSize, void* data);

		void SetImage(std::vector<Render::Texture>& images)
		{
			this->images = images;
		};

		virtual void Render(Render::ShaderProgram* program, Render::Material* material);
	protected:
		unsigned int ebo;
		unsigned int vbo;
		unsigned int tvao;
		unsigned int verticesNum = 0;
		std::vector<Render::Texture> images;

		std::string m_name;
	};

}
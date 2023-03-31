#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "../file/Image.h"
#include "Texture.h"
#include "../opengl/OpenGLCore.h"
#include "../opengl/GLShader.h"
#include "../render/Material.h"
#include "RenderBaseMesh.h"

namespace Render
{
	/*
		mesh 数据，对应一个vbo
		顶点，uv，光照贴图 等等
	*/

	class RenderUIMesh : public RenderBaseMesh
	{
		friend class FontManager;
	public:
		RenderUIMesh(std::string name);
	
		virtual void Render(Render::ShaderProgram* program, Render::Material* material);
	private:
	};


}
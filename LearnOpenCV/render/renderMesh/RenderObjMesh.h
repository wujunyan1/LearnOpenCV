#pragma once

#include <map>
#include "../math/Math.h"
#include "RenderBaseMesh.h"

namespace Render
{
	/*
		mesh 数据，对应一个vbo
		顶点，uv，光照贴图 等等
	*/
	class RenderObjMesh : public RenderBaseMesh
	{
	public:
		RenderObjMesh(std::string name);
		~RenderObjMesh();

		virtual void Render(Render::ShaderProgram* program, Render::Material* material);
	protected:
		
	};

}
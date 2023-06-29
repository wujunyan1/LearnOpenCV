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
	class RenderCustomMesh : public RenderBaseMesh
	{
	public:
		RenderCustomMesh(std::string name);
		~RenderCustomMesh();

		virtual void Render(Render::ShaderProgram* program, Render::Material* material);
		virtual void RenderInstances(Render::ShaderProgram* program, Render::Material* material, unsigned int count);

	protected:

	};

}
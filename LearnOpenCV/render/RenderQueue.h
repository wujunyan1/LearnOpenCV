#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "Material.h"

namespace Render
{
	class RenderProgram
	{
	public:
		void setVBO(unsigned int _vbo) { vbo = _vbo; }
		unsigned int getVBO() { return vbo; }

	private:
		unsigned int vbo;

		ShaderProgram* shaderProgram;

		Material* material;
	};


	class RenderQueue
	{
	public:



	private:

		// 这个队列的shader
		ShaderProgram* shaderProgram;

		// 激活的需要渲染的
		std::vector<Material>	activeMaterial;
	};

}
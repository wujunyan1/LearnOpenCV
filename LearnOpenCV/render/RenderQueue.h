#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "RenderMesh.h"

namespace Render
{
	class RenderProgram
	{
	public:
		RenderProgram();

		void setVBO(unsigned int _vbo) { vbo = _vbo; }
		unsigned int getVBO() { return vbo; }

		virtual RenderMesh* createNewRenderMesh(std::string name = Math::getUid()) { return NULL; };
		virtual RenderMesh* loadRenderMesh(std::string name, std::string path = "") { return NULL; };

		RenderMesh* getMesh() { return mesh; }

		ShaderProgram* getShaderProgram() { return shaderProgram; }
		Material* getMaterial() { return material; }

		virtual void setShader(const std::string& shaderName) {};

		virtual void Render() {};
	protected:
		unsigned int vbo;

		ShaderProgram* shaderProgram;

		Material* material;

		RenderMesh* mesh;
	};
}
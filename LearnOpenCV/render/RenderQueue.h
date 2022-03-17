#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "RenderMesh.h"

#include "../meshModel/AModel.h"

namespace Render
{
	class RenderProgram
	{
	public:
		RenderProgram();

		void setVBO(unsigned int _vbo) { vbo = _vbo; }
		unsigned int getVBO() { return vbo; }

		virtual RenderMesh* createNewRenderMesh(std::string name = Math::stringFormat("renderMesh|%d", Math::getUid())) { return NULL; };
		virtual RenderMesh* loadRenderMesh(std::string name, std::string path = "") { return NULL; };

		std::vector <RenderMesh*>* getMeshs() { return meshs; }
		void addMesh(RenderMesh* mesh) { 
			if (!meshs) {
				meshs = new std::vector<RenderMesh*>();
			}
			meshs->push_back(mesh); 
		}
		virtual void addModel(Core::AModel* model) {};

		ShaderProgram* getShaderProgram() { return shaderProgram; }
		Material* getMaterial() { return material; }

		virtual void setShader(const std::string& shaderName) {};

		virtual void Render() {};
	protected:
		unsigned int vbo;

		ShaderProgram* shaderProgram;

		Material* material;

		std::vector<RenderMesh*>* meshs;
	};
}
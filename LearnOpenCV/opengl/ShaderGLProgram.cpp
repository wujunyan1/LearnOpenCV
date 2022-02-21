#include "ShaderGLProgram.h"
#include "MaterialGL.h"
#include "GLShaderManager.h"

namespace OpenGL
{
	std::map<std::string, ShaderGLProgram*>* ShaderGLProgram::programs = new std::map<std::string, ShaderGLProgram*>();

	ShaderGLProgram* ShaderGLProgram::GetShaderGLProgram(const std::string& shaderName)
	{
		auto it = programs->find(shaderName);
		if (it != programs->end())
		{
			return it->second;
		}

		unsigned int shaderId = GLShaderManager::Instance()->GetShader(shaderName);
		if (shaderId != 0)
		{
			ShaderGLProgram* newProgram = new ShaderGLProgram();
			newProgram->shaderName = shaderName;
			programs->insert(std::pair<std::string, ShaderGLProgram*>(shaderName, newProgram));
			return newProgram;
		}

		return NULL;
	}

	void ShaderGLProgram::RenderMaterial(Render::Material* material)
	{

	}

	void ShaderGLProgram::SetVSAndPS(std::string vs, std::string ps)
	{

	}

	GLShader* ShaderGLProgram::GetShaderObj()
	{
		return GLShaderManager::Instance()->GetShaderObj(shaderName);
	}

	void ShaderGLProgram::Use()
	{

	}

}
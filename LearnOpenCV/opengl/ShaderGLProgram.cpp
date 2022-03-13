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
		RenderMaterial(dynamic_cast<OpenGL::MaterialGL*>(material));
	}

	void ShaderGLProgram::RenderMaterial(OpenGL::MaterialGL* material)
	{
		GLShader* shader = GetShaderObj();
		std::vector<Render::ShaderParam> params = material->getShaderParams();
		for( Render::ShaderParam param : params)
		{
			Render::ShaderParamType stype = param.stype;
			switch (stype)
			{
			case Render::ShaderParamType::SPT_UNKNOWN:
				break;
			case Render::ShaderParamType::SPT_INT:
				shader->setInt(param.name, param.data.getDataPtr());
				break;
			case Render::ShaderParamType::SPT_FLOAT:
				shader->setFloat(param.name, param.data.getDataPtr());
				break;
			case Render::ShaderParamType::SPT_VEC2:
				break;
			case Render::ShaderParamType::SPT_VEC3:
				shader->setVec3(param.name, param.data.getDataPtr());
				break;
			case Render::ShaderParamType::SPT_VEC4:
				shader->setFloat4(param.name, param.data.getDataPtr());
				break;
			case Render::ShaderParamType::SPT_MAT4:
				shader->setMat4(param.name, param.data.getDataPtr());
				break;
			case Render::ShaderParamType::SPT_TEXTURE:
				break;
			default:
				break;
			}
		}

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
		GLShader* shader = GetShaderObj();
		shader->use();
	}

}
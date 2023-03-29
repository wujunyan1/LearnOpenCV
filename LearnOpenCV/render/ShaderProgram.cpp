#include "ShaderProgram.h"
#include "Material.h"

#include "../opengl/GLShader.h"
#include "../opengl/GLShaderManager.h"

namespace Render
{
	ShaderParam::ParamData::ParamData()
	{
		
	}

	ShaderParam::ParamData::ParamData(const ParamData& other)
	{
		copySize = other.copySize;
		if (copySize)
		{
			auto temp = malloc(copySize);
			memcpy(temp, other.data, copySize);
			data = temp;
		}
		else
		{
			data = other.data;
		}
	}

	ShaderParam::ParamData::ParamData(ParamData&& other) noexcept
	{
		data = other.data;
		copySize = other.copySize;
		other.data = nullptr;
		other.copySize = 0;
	}

	ShaderParam::ParamData& ShaderParam::ParamData::operator=(ParamData other) noexcept
	{
		std::swap(data, other.data);
		std::swap(copySize, other.copySize);
		return *this;
	}

	ShaderParam::ParamData::~ParamData()
	{
		if (data && copySize)
			::free((void*)data);
	}

	void ShaderParam::ParamData::setData(const void* data, int copySize)
	{
		reset();
		if (copySize)
		{
			auto temp = malloc(copySize);
			memcpy(temp, data, copySize);
			this->copySize = copySize;
			this->data = temp;
		}
		else
		{
			this->copySize = 0;
			this->data = data;
		}
	}

	void ShaderParam::ParamData::reset()
	{
		*this = {};
	}

	std::map<std::string, ShaderProgram*>* ShaderProgram::programs = new std::map<std::string, ShaderProgram*>();

	ShaderProgram* ShaderProgram::GetShaderProgram(const std::string& shaderName)
	{
		auto it = programs->find(shaderName);
		if (it != programs->end())
		{
			return it->second;
		}

		unsigned int shaderId = GLShaderManager::Instance()->GetShader(shaderName);
		if (shaderId != 0)
		{
			ShaderProgram* newProgram = new ShaderProgram(shaderId);
			newProgram->shaderName = shaderName;
			programs->insert(std::pair<std::string, ShaderProgram*>(shaderName, newProgram));
			return newProgram;
		}

		return NULL;
	}

	bool ShaderProgram::checkSameParams(std::string& name, const void* data)
	{
		auto it = m_currParams.find(name);
		if (it == m_currParams.end())
		{
			//m_currParams.insert(std::pair<std::string, void*>(name, data));
			m_currParams[name] = data;
			return false;
		}

		if (it->second == data) {
			return true;
		}
		m_currParams[name] = data;
		return false;
	}


	void ShaderProgram::setMat4(const std::string& name, Math::Matrix4& mat)
	{
		GLShader* shader = GetShaderObj();
		shader->setMat4(name, mat);
	}

	void ShaderProgram::RenderMaterial(Render::Material* material)
	{
		GLShader* shader = GetShaderObj();

		std::vector<Render::ShaderParam>& params = material->getShaderParams();
		for (Render::ShaderParam param : params)
		{
			Render::ShaderParamType stype = param.stype;
			switch (stype)
			{
			case Render::ShaderParamType::SPT_UNKNOWN:
				break;
			case Render::ShaderParamType::SPT_INT:
				if (!checkSameParams(param.name, param.data.getDataPtr())) {
					shader->setInt(param.name, param.data.getDataPtr());
				}
				break;
			case Render::ShaderParamType::SPT_FLOAT:
				if (!checkSameParams(param.name, param.data.getDataPtr())) {
					shader->setFloat(param.name, param.data.getDataPtr());
				}
				break;
			case Render::ShaderParamType::SPT_VEC2:
				break;
			case Render::ShaderParamType::SPT_VEC3:
				if (!checkSameParams(param.name, param.data.getDataPtr())) {
					shader->setVec3(param.name, param.data.getDataPtr());
				}
				break;
			case Render::ShaderParamType::SPT_VEC4:
				if (!checkSameParams(param.name, param.data.getDataPtr())) {
					shader->setFloat4(param.name, param.data.getDataPtr());
				}
				break;
			case Render::ShaderParamType::SPT_MAT4:
				if (!checkSameParams(param.name, param.data.getDataPtr())) {
					shader->setMat4(param.name, param.data.getDataPtr());
				}
				break;
			case Render::ShaderParamType::SPT_TEXTURE:
				break;
			default:
				break;
			}
		}
	}

	void ShaderProgram::SetVSAndPS(std::string vs, std::string ps)
	{

	}

	GLShader* ShaderProgram::GetShaderObj()
	{
		return GLShaderManager::Instance()->GetShaderObj(shaderName);
	}

	void ShaderProgram::Use()
	{
		GLShader* shader = GetShaderObj();
		shader->use();

		m_currParams.clear();
	}

}
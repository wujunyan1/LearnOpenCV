#pragma once

#include "OpenGLCore.h"
#include "../render/ShaderProgram.h"
#include "../render/Material.h"
#include "ShaderGLProgram.h"

namespace OpenGL
{
	// shader 的参数信息
	class MaterialGL : public Render::Material
	{
	public:

		void setBool(const std::string& name, bool value);
		void setInt(const std::string& name, int value);
		void setFloat(const std::string& name, float value);
		void setFloat4(const std::string& name, float r, float g, float b, float a);
		void setVec3(const std::string& name, Math::Vector3& value);
		void setVec3(const std::string& name, float x, float y, float z);
		void setMat4(const std::string& name, Math::Matrix4& mat);
		void setTexture(const std::string& name, Render::Texture& texture);

		std::vector<Render::ShaderParam>& getShaderParams() { return m_ShaderParams; }
		std::vector<Render::Texture>& getShaderTextures() { return m_shaderTextures; };

		void testPrint(std::string pr);

	private:
		int getParamPhysicsIndex(const std::string& name);
		int tryModifyShaderParam(const std::string& name, void* data, Render::ShaderParamType stype, int copySize = 0);
		void insertData(const std::string& name, void* data, Render::ShaderParamType stype, int copySize);
		void setData(const std::string& name, const int index, void* data, Render::ShaderParamType stype, int copySize);

	private:

		// shader参数
		std::vector<Render::ShaderParam>	m_ShaderParams;

		std::vector<Render::Texture> m_shaderTextures;
	};

}
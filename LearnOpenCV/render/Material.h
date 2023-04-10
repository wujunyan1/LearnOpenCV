#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace Render
{
	// shader 的参数信息
	class Material
	{
	public:

		virtual void setBool(const std::string& name, bool value);
		virtual void setInt(const std::string& name, int value);
		virtual void setFloat(const std::string& name, float value);
		virtual void setFloat4(const std::string& name, float r, float g, float b, float a);
		virtual void setVec2(const std::string& name, Math::Vector2& value);
		virtual void setVec2(const std::string& name, float x, float y);
		virtual void setVec3(const std::string& name, Math::Vector3& value);
		virtual void setVec3(const std::string& name, float x, float y, float z);
		virtual void setMat4(const std::string& name, Math::Matrix4& mat);
		virtual void setTexture(const std::string& name, Texture& texture);
		void clearTexture() { m_shaderTextures.clear(); };

		virtual const void* getData(const std::string& name);

		std::vector<Render::ShaderParam>& getShaderParams() { return m_ShaderParams; }
		std::vector<Render::Texture>& getShaderTextures() { return m_shaderTextures; };

		void testPrint(std::string pr);

	private:
		int getParamPhysicsIndex(const std::string& name);
		int tryModifyShaderParam(const std::string& name, void* data, Render::ShaderParamType stype, int copySize = 0);
		void insertData(const std::string& name, void* data, Render::ShaderParamType stype, int copySize);
		void setData(const std::string& name, const int index, void* data, Render::ShaderParamType stype, int copySize);

	protected:

		// shader参数
		std::vector<Render::ShaderParam>	m_ShaderParams;

		std::vector<Render::Texture> m_shaderTextures;
	};

}
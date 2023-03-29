#pragma once

#include <map>
#include "../math/Math.h"
#include "../opengl/GLShader.h"

namespace Render
{

	class Material;

	struct ShaderParam
	{
		class ParamData
		{
		public:
			ParamData();
			ParamData(const ParamData& other);
			ParamData(ParamData&& other) noexcept;
			ParamData& operator=(ParamData other) noexcept;
			~ParamData();
			void setData(const void* data, int copySize = 0);
			const void* getDataPtr() const { return data; }
			void reset();

		private:
			const void* data = nullptr;
			int copySize = 0;  // equals to 0 if don't need to free data automatically, otherwise equals to size of data
		};

		std::string			name;
		ShaderParamType		stype;
		unsigned int		physicsIndex;
		unsigned int		paramsLength;  // shader constance register num.
		ParamData			data;
	};

	// 某个Shader渲染
	class ShaderProgram
	{
	public:

		ShaderProgram(unsigned int shaderId): shader(shaderId) {};

		virtual void RenderMaterial(Material* material);

		bool operator == (const ShaderProgram& rhs)
		{
			return shader == rhs.shader;
		}

		bool operator != (const ShaderProgram& rhs)
		{
			return shader != rhs.shader;
		}

		unsigned int GetShader()
		{
			return shader;
		}

		virtual void SetVSAndPS(std::string vs, std::string ps);

		virtual void Use();

		virtual void setMat4(const std::string& name, Math::Matrix4& mat);

		GLShader* GetShaderObj();

		static ShaderProgram* GetShaderProgram(const std::string& shaderName);

	private:
		bool checkSameParams(std::string& name, const void* data);

	protected:

		// 绑定的shader
		unsigned int shader;

	private:

		std::string shaderName;

		// 当前的 shader参数
		std::map<std::string, const void*> m_currParams;

	private:
		static std::map<std::string, ShaderProgram*>* programs;
	};

}
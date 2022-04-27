#pragma once

#include <map>
#include "../math/Math.h"

namespace Render
{
	// 支持的着色器参数类型
	enum class ShaderParamType
	{
		SPT_UNKNOWN = 0,
		SPT_INT,
		SPT_FLOAT,
		SPT_VEC2,
		SPT_VEC3,
		SPT_VEC4,
		SPT_MAT4,
		SPT_TEXTURE,
	};

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

		virtual void RenderMaterial(Material* material) {};

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

		virtual void SetVSAndPS(std::string vs, std::string ps) {};

		virtual void Use() {};

	protected:

		// 绑定的shader
		unsigned int shader;
	};

}
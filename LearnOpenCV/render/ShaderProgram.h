#pragma once

#include <map>
#include "../math/Math.h"

namespace Render
{
	// ֧�ֵ���ɫ����������
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

	// ĳ��Shader��Ⱦ
	class ShaderProgram
	{
	public:
		struct ShaderParam
		{
			class ParamData
			{
			public:
				ParamData() = default;
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


		void RenderMaterial(Material* material);

	protected:

		// �󶨵�shader
		unsigned int shader;

		// ��ǰ�� shader����
		std::vector<ShaderProgram::ShaderParam> s_ShaderParams;
	};

}
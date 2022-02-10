#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"

namespace Render
{
	
	class Material
	{
	public:



	private:
		// 对应的shader
		ShaderProgram* renderProgram;

		// shader参数
		std::vector<ShaderProgram::ShaderParam>	m_ShaderParams;
	};

}
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
		// ��Ӧ��shader
		ShaderProgram* renderProgram;

		// shader����
		std::vector<ShaderProgram::ShaderParam>	m_ShaderParams;
	};

}
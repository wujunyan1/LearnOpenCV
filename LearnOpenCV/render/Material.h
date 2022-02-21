#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"

namespace Render
{
	// shader 的参数信息
	class Material
	{
	public:

		virtual void setBool(const std::string& name, bool value) {};
		virtual void setInt(const std::string& name, int value) {};
		virtual void setFloat(const std::string& name, float value) {};
		virtual void setFloat4(const std::string& name, float r, float g, float b, float a) {};
		virtual void setVec3(const std::string& name, Math::Vector3 value) {};
		virtual void setVec3(const std::string& name, float x, float y, float z) {};
		virtual void setMat4(const std::string& name, Math::Matrix4 mat) {};


	protected:

	};

}
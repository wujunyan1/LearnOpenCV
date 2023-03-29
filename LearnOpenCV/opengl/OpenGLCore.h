#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

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

	unsigned int GET_OPENGL_TYPE(Render::ShaderParamType dataType);

	void checkGLError(const char* message);
	void checkGLError(const char* file, int line);
	const char* toGLErrorString(GLenum error);
#define GL_GET_ERROR(x) do {x; Render::checkGLError(__FILE__, __LINE__);}while(false);
}
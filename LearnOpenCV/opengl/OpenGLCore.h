#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include "../render/ShaderProgram.h"

namespace OpenGL
{
	unsigned int GET_OPENGL_TYPE(Render::ShaderParamType dataType);
}
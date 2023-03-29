#include "OpenGLCore.h"

namespace Render
{
    unsigned int GET_OPENGL_TYPE(Render::ShaderParamType dataType)
    {
        switch (dataType)
        {
        case Render::ShaderParamType::SPT_INT:
            return GL_INT;
        case Render::ShaderParamType::SPT_FLOAT:
            return GL_FLOAT;
        case Render::ShaderParamType::SPT_TEXTURE:
            return GL_TEXTURE;
        default:
            return GL_FLOAT;
        }

        return GL_FLOAT;
    }



	void checkGLError(const char* message)
	{
		GLenum error;
		while ((error = glGetError()) != GL_NO_ERROR)
		{
			const char* errorName = toGLErrorString(error);
			printf("GLError [%x] %s: %s", error, errorName, message);
		}
	}

	void checkGLError(const char* file, int line)
	{
		GLenum error;
		while ((error = glGetError()) != GL_NO_ERROR)
		{
			const char* errorName = toGLErrorString(error);
			printf("GLError [%x] %s %s, line %d \n", error, errorName, file, line);
		}
	}

	const char* toGLErrorString(GLenum error)
	{
		switch (error)
		{
		case GL_INVALID_ENUM:                  return "INVALID_ENUM";
		case GL_INVALID_VALUE:                 return "INVALID_VALUE";
		case GL_INVALID_OPERATION:             return "INVALID_OPERATION";
		case GL_STACK_OVERFLOW:                return "STACK_OVERFLOW";
		case GL_STACK_UNDERFLOW:               return "STACK_UNDERFLOW";
		case GL_OUT_OF_MEMORY:                 return "OUT_OF_MEMORY";
		case GL_INVALID_FRAMEBUFFER_OPERATION: return "INVALID_FRAMEBUFFER_OPERATION";
		default:                               return "UNKNOWN_ERR";
		}
	}

}
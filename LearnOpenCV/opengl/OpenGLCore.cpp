#include "OpenGLCore.h"

#include "../render/ShaderProgram.h"

namespace OpenGL
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
}
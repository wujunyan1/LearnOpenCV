#include "MaterialGL.h"

namespace OpenGL
{

    void MaterialGL::setBool(const std::string& name, bool value)
    {
        Render::ShaderParam shaderParam;

        m_ShaderParams.push_back(shaderParam);
    }
    void MaterialGL::setInt(const std::string& name, int value)
    {
        
    }
    void MaterialGL::setFloat(const std::string& name, float value)
    {
        
    }

    void MaterialGL::setVec3(const std::string& name, Math::Vector3 value)
    {
    }

    void MaterialGL::setVec3(const std::string& name, float x, float y, float z)
    {
    }


    void MaterialGL::setFloat4(const std::string& name, float r, float g, float b, float a)
    {
    }

    void MaterialGL::setMat4(const std::string& name, Math::Matrix4 mat)
    {
    }



}
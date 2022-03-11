#include "MaterialGL.h"
#include "GLShaderManager.h"

namespace OpenGL
{

    int MaterialGL::getParamPhysicsIndex(const std::string& name)
    {
        for (auto i : m_ShaderParams)
        {
            if (i.name == name)
            {
                return i.physicsIndex;
            }
        }

        return -1;
    }

    void MaterialGL::insertData(const std::string& name, void* data, Render::ShaderParamType stype, int copySize)
    {
        Render::ShaderParam shaderParam;
        shaderParam.name = name;
        shaderParam.data.setData(data, copySize);
        shaderParam.stype = stype;
        shaderParam.paramsLength = 1;
        shaderParam.physicsIndex = m_ShaderParams.size();

        m_ShaderParams.push_back(shaderParam);
    }

    void MaterialGL::setData(const std::string& name, const int index, void* data, Render::ShaderParamType stype, int copySize)
    {
        Render::ShaderParam shaderParam = m_ShaderParams.at(index);
        shaderParam.data.setData(data, copySize);
        shaderParam.stype = stype;
    }

    int MaterialGL::tryModifyShaderParam(const std::string& name, void* data, Render::ShaderParamType stype, int copySize)
    {
        printf("xx22222222xxxxx %p %d \n", data, copySize);
        int index = getParamPhysicsIndex(name);

        if (index == -1)
        {
            insertData(name, data, stype, copySize);
        }
        else
        {
            setData(name, index, data, stype, copySize);
        }

        return index;
    }

    void MaterialGL::setBool(const std::string& name, bool value)
    {
        int v = value ? 1 : 0;
        tryModifyShaderParam(name, &v, Render::ShaderParamType::SPT_INT, sizeof(int));
    }

    void MaterialGL::setInt(const std::string& name, int value)
    {
        tryModifyShaderParam(name, &value, Render::ShaderParamType::SPT_INT, sizeof(value));
    }

    void MaterialGL::setFloat(const std::string& name, float value)
    {
        tryModifyShaderParam(name, &value, Render::ShaderParamType::SPT_FLOAT, sizeof(value));
    }

    void MaterialGL::setVec3(const std::string& name, Math::Vector3 value)
    {
        tryModifyShaderParam(name, &value, Render::ShaderParamType::SPT_VEC3, sizeof(value));
    }

    void MaterialGL::setVec3(const std::string& name, float x, float y, float z)
    {
        Math::Vector3 v = Math::Vector3(x, y, z);
        tryModifyShaderParam(name, &v, Render::ShaderParamType::SPT_VEC3, sizeof(v));
    }


    void MaterialGL::setFloat4(const std::string& name, float r, float g, float b, float a)
    {
        Math::Vector4 v = Math::Vector4(r, g, b, a);
        tryModifyShaderParam(name, &v, Render::ShaderParamType::SPT_VEC4, sizeof(v));
    }

    void MaterialGL::setMat4(const std::string& name, Math::Matrix4& mat)
    {
        printf("xx111111111112xxxxx %p \n", &mat);
        tryModifyShaderParam(name, (void*)&mat, Render::ShaderParamType::SPT_MAT4, sizeof(mat));
    }


}
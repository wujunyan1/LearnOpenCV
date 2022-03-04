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

    void MaterialGL::insertData(const std::string& name, void* data, Render::ShaderParamType stype)
    {
        Render::ShaderParam shaderParam;
        shaderParam.name = name;
        shaderParam.data.setData(data);
        shaderParam.stype = stype;
        shaderParam.paramsLength = 1;
        shaderParam.physicsIndex = m_ShaderParams.size();

        m_ShaderParams.push_back(shaderParam);
    }

    void MaterialGL::setData(const std::string& name, const int index, void* data, Render::ShaderParamType stype)
    {
        Render::ShaderParam shaderParam = m_ShaderParams.at(index);
        shaderParam.data.setData(data);
        shaderParam.stype = stype;
    }

    int MaterialGL::tryModifyShaderParam(const std::string& name, void* data, Render::ShaderParamType stype)
    {
        printf("xx22222222xxxxx %p \n", data);
        int index = getParamPhysicsIndex(name);

        if (index == -1)
        {
            insertData(name, data, stype);
        }
        else
        {
            setData(name, index, data, stype);
        }


        float* f = (float*)data;
        printf("xxxxxxxxxxxxxxxxxxxx \n");
        printf("%f %f %f %f \n", f[0], f[1], f[2], f[3]);
        printf("%f %f %f %f \n", f[4], f[5], f[6], f[7]);
        printf("%f %f %f %f \n", f[8], f[9], f[10], f[11]);
        printf("%f %f %f %f \n", f[12], f[13], f[14], f[15]);

        return index;
    }

    void MaterialGL::setBool(const std::string& name, bool value)
    {
        int v = value ? 1 : 0;
        tryModifyShaderParam(name, &v, Render::ShaderParamType::SPT_INT);
    }

    void MaterialGL::setInt(const std::string& name, int value)
    {
        tryModifyShaderParam(name, &value, Render::ShaderParamType::SPT_INT);
    }

    void MaterialGL::setFloat(const std::string& name, float value)
    {
        tryModifyShaderParam(name, &value, Render::ShaderParamType::SPT_FLOAT);
    }

    void MaterialGL::setVec3(const std::string& name, Math::Vector3 value)
    {
        tryModifyShaderParam(name, &value, Render::ShaderParamType::SPT_VEC3);
    }

    void MaterialGL::setVec3(const std::string& name, float x, float y, float z)
    {
        Math::Vector3 v = Math::Vector3(x, y, z);
        tryModifyShaderParam(name, &v, Render::ShaderParamType::SPT_VEC3);
    }


    void MaterialGL::setFloat4(const std::string& name, float r, float g, float b, float a)
    {
        Math::Vector4 v = Math::Vector4(r, g, b, a);
        tryModifyShaderParam(name, &v, Render::ShaderParamType::SPT_VEC3);
    }

    void MaterialGL::setMat4(const std::string& name, Math::Matrix4 mat)
    {
        printf("xx111111111112xxxxx %p \n", &mat);
        tryModifyShaderParam(name, &mat, Render::ShaderParamType::SPT_MAT4);
    }


}
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "OpenGLCore.h"
#include "../math/Math.h"

class GLShader
{
public:

    // 构造器读取并构建着色器
    GLShader(unsigned int vertex, unsigned int  fragment);
    ~GLShader();

    // 使用/激活程序
    void use();
    // uniform工具函数
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setFloat4(const std::string& name, float r, float g, float b, float a) const;
    void setVec3(const std::string& name, Math::Vector3 value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setMat4(const std::string& name, Math::Matrix4 mat) const;

    unsigned int getID() { return ID; };
public:
    // 程序ID
    unsigned int ID;

    unsigned int vs;
    unsigned int fs;
};
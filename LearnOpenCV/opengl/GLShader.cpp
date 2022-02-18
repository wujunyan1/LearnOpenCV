#include "GLShader.h"
#include "../file/FilePathManager.h"

GLShader::GLShader(unsigned int vertex, unsigned int  fragment)
{
    
    // 2. 编译着色器
    int success;
    char infoLog[512];

    // 着色器程序
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // 打印连接错误（如果有的话）
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    // glDeleteShader(vertex);
    // glDeleteShader(fragment);
}

GLShader::~GLShader()
{

}

void GLShader::use()
{
    glUseProgram(ID);
}

void GLShader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void GLShader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void GLShader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void GLShader::setVec3(const std::string& name, Math::Vector3 value) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void GLShader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}


void GLShader::setFloat4(const std::string& name, float r, float g, float b, float a) const
{
    int vertexColorLocation = glGetUniformLocation(ID, name.c_str());
    glUniform4f(vertexColorLocation, r , g, b, a);
}

void GLShader::setMat4(const std::string& name, Math::Matrix4 mat) const
{
    int modelLoc = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)&mat);
}

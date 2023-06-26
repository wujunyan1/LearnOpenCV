#include "GLShader.h"
#include "../file/FilePathManager.h"
#include "../render/RenderMain.h"

GLShader::GLShader(unsigned int vertex, unsigned int  fragment)
{
    fs = fragment;
    vs = vertex;

    // 2. 编译着色器
    int success;
    char infoLog[512];

    // 着色器程序
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    GL_GET_ERROR(glLinkProgram(ID));
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
    GL_GET_ERROR(glUseProgram(ID));
}

void GLShader::setBool(const std::string& name, bool value) const
{
    
	GL_GET_ERROR(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value));
}
void GLShader::setInt(const std::string& name, int value) const
{
    GL_GET_ERROR(glUniform1i(glGetUniformLocation(ID, name.c_str()), value));
}
void GLShader::setFloat(const std::string& name, float value) const
{
    GL_GET_ERROR(glUniform1f(glGetUniformLocation(ID, name.c_str()), value));
}

void GLShader::setVec2(const std::string& name, Math::Vector2 value) const
{
    GL_GET_ERROR(glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y));
}

void GLShader::setVec2Array(const std::string& name, int arrayNum, float* value) const
{
    //GL_GET_ERROR(location = glGetUniformLocation(ID, name.c_str()));
    //GL_GET_ERROR(glUniform2fv(location, arrayNum, value));

    /*int activeUniformLength;
    glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &activeUniformLength);

    for (size_t i = 0; i < activeUniformLength; i++)
    {
        int uniformLength;
        GLint uniformSize;
        GLenum uniformType;
        GLchar unname;
        char* c = &unname;

        glGetActiveUniform(ID, i, 512, &uniformLength, &uniformSize, &uniformType, c);

        for (size_t j = 0; j < uniformLength; j++)
        {
            printf("%c", *c);
            c++;
        }
        printf("\n");
    }*/

    GL_GET_ERROR(glUniform2fv(glGetUniformLocation(ID, name.c_str()), arrayNum, value));
}

void GLShader::setVec3(const std::string& name, Math::Vector3 value) const
{
    GL_GET_ERROR(glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z));
}

void GLShader::setVec3(const std::string& name, float x, float y, float z) const
{
    GL_GET_ERROR(glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z));
}


void GLShader::setFloat4(const std::string& name, float r, float g, float b, float a) const
{
    int vertexColorLocation = glGetUniformLocation(ID, name.c_str());
    GL_GET_ERROR(glUniform4f(vertexColorLocation, r , g, b, a));
}

void GLShader::setMat4(const std::string& name, Math::Matrix4 mat) const
{
    int modelLoc = glGetUniformLocation(ID, name.c_str());
    GL_GET_ERROR(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)&mat));
}

void GLShader::setTexture(const std::string& name, unsigned int index) const
{
    GL_GET_ERROR(glUniform1i(glGetUniformLocation(ID, name.c_str()), index));
}

void GLShader::setBool(const std::string& name, const void* value) const
{
    GL_GET_ERROR(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value));
}

void GLShader::setInt(const std::string& name, const void* value) const
{
    GL_GET_ERROR(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value));
}

void GLShader::setFloat(const std::string& name, const void* value) const
{
    GLfloat f = *(GLfloat*)(&value);
    GL_GET_ERROR(glUniform1f(glGetUniformLocation(ID, name.c_str()), f));
}

void GLShader::setFloat4(const std::string& name, const void* value) const
{
    GL_GET_ERROR(glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, (float*)(value)));
}

void GLShader::setVec3(const std::string& name, const void* value) const
{
    GL_GET_ERROR(glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, (GLfloat*)value));
}

void GLShader::setMat4(const std::string& name, const void* mat) const
{
    /*printf("!!!!!!!! %p \n", &mat);
    float* f = (float*)mat;
    printf("=================== %s \n", name.c_str());
    printf("%f %f %f %f \n", f[0], f[1], f[2], f[3]);
    printf("%f %f %f %f \n", f[4], f[5], f[6], f[7]);
    printf("%f %f %f %f \n", f[8], f[9], f[10], f[11]);
    printf("%f %f %f %f \n", f[12], f[13], f[14], f[15]);*/

    int modelLoc = glGetUniformLocation(ID, name.c_str());
    GL_GET_ERROR(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)mat));
}


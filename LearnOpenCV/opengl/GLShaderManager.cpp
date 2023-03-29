#include "GLShaderManager.h"

#include "../file/FilePathManager.h"

namespace Render
{
    GLShaderManager* GLShaderManager::ms_pSingleton_impl = NULL;

    unsigned int GLShaderManager::LoadVertexShader(std::string path)
    {
        // 1. 从文件路径中获取顶点/片段着色器
        std::string vertexCode;
        std::ifstream vShaderFile;
        // 保证ifstream对象可以抛出异常：
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            std::string s = std::string(FilePathManager::getRootPath());
            // 打开文件
            vShaderFile.open((s + std::string(path)).c_str());
            std::stringstream vShaderStream;
            // 读取文件的缓冲内容到数据流中
            vShaderStream << vShaderFile.rdbuf();
            // 关闭文件处理器
            vShaderFile.close();
            // 转换数据流到string
            vertexCode = vShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            printf(e.what());
        }
        const char* vShaderCode = vertexCode.c_str();

        // 2. 编译着色器
        unsigned int vertex;
        int success;
        char infoLog[512];

        // 顶点着色器
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // 打印编译错误（如果有的话）
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

            return 0;
        };

        return vertex;
    }

    unsigned int GLShaderManager::LoadFragmentShader(std::string path)
    {
        // 1. 从文件路径中获取顶点/片段着色器
        std::string fragmentCode;
        std::ifstream fShaderFile;
        // 保证ifstream对象可以抛出异常：
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            std::string s = std::string(FilePathManager::getRootPath());
            // 打开文件

            fShaderFile.open((s + std::string(path)).c_str());
            std::stringstream fShaderStream;
            // 读取文件的缓冲内容到数据流中
            fShaderStream << fShaderFile.rdbuf();
            // 关闭文件处理器
            fShaderFile.close();
            // 转换数据流到string
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            printf(e.what());
        }
        const char* fShaderCode = fragmentCode.c_str();


        // 2. 编译着色器
        unsigned int fragment;
        int success;
        char infoLog[512];

        // 片源着色器
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        // 打印编译错误（如果有的话）
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        return fragment;
    }

	unsigned int GLShaderManager::GetVertex(std::string path)
	{
		return LoadVertexShader(path);
	}

	unsigned int GLShaderManager::GetFragment(std::string path)
	{
        return LoadFragmentShader(path);
	}

	unsigned int GLShaderManager::GetShader(std::string name)
	{
        auto it = shader_ids->find(name);
        if (it == shader_ids->end())
        {
            return 0;
        }
        else
        {
            GLShader* shader = it->second;
            return shader->getID();
        }
	}

	unsigned int GLShaderManager::GetShader(std::string name, std::string vs, std::string fs)
	{
        auto it = shader_ids->find(name);
        if (it == shader_ids->end())
        {
            unsigned v = GetVertex(vs);
            unsigned f = GetFragment(fs);

            GLShader* shader = new GLShader(v, f);
            shader_ids->insert(std::pair<std::string, GLShader*>(name, shader));

            glDeleteShader(v);
            glDeleteShader(f);

            return shader->getID();
        }
        else
        {
            GLShader* shader = it->second;
            return shader->getID();
        }
	}


    GLShader* GLShaderManager::GetShaderObj(std::string name)
    {
        auto it = shader_ids->find(name);
        if (it == shader_ids->end())
        {
            return NULL;
        }
        else
        {
            return it->second;
        }
    }
}
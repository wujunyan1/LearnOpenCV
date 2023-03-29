#pragma once

#include <map>
#include "GLShader.h"

namespace Render
{
	// Ä³¸öShaderäÖÈ¾
	class GLShaderManager
	{
	public:
		static GLShaderManager* Instance()
		{
			return ms_pSingleton_impl;
		}

		static void NewInstance()
		{
			ms_pSingleton_impl = new GLShaderManager();
		}

	public:

		unsigned int GetVertex(std::string path);
		unsigned int GetFragment(std::string path);
		unsigned int GetShader(std::string name);

		unsigned int GetShader(std::string name, std::string vs, std::string fs);

		GLShader* GetShaderObj(std::string name);
	private:
		unsigned int LoadVertexShader(std::string path);
		unsigned int LoadFragmentShader(std::string path);

	private:
		GLShaderManager() {
			shader_ids = new std::map<std::string, GLShader*>();
		};

	private:
		std::map<std::string, GLShader*>* shader_ids;

		static GLShaderManager* ms_pSingleton_impl;
	};

}
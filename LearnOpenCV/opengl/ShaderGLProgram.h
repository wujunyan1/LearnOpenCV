#pragma once

#include <map>

#include "../render/ShaderProgram.h"
#include "GLShader.h"

namespace OpenGL
{
	class MaterialGL;
	// ĳ��Shader��Ⱦ
	class ShaderGLProgram : public Render::ShaderProgram
	{
	public:

		void RenderMaterial(Render::Material* material);
		void RenderMaterial(OpenGL::MaterialGL* material);

		void SetVSAndPS(std::string vs, std::string ps);

		GLShader* GetShaderObj();

		void Use();

		static ShaderGLProgram* GetShaderGLProgram(const std::string& shaderName);

	private:
		bool checkSameParams(std::string& name, const void* data);

	private:

		std::string shaderName;

		// ��ǰ�� shader����
		std::map<std::string, const void*> m_currParams;

	private:
		static std::map<std::string, ShaderGLProgram*>* programs;
	};

}
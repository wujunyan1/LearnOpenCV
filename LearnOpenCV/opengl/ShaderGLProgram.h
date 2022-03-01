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

		std::string shaderName;

		// ��ǰ�� shader����
		std::vector<Render::ShaderParam> s_ShaderParams;

	private:
		static std::map<std::string, ShaderGLProgram*>* programs;
	};

}
#pragma once

#include <map>

#include "../render/ShaderProgram.h"
#include "GLShader.h"

namespace OpenGL
{
	class MaterialGL;
	// 某个Shader渲染
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

		// 当前的 shader参数
		std::vector<Render::ShaderParam> s_ShaderParams;

	private:
		static std::map<std::string, ShaderGLProgram*>* programs;
	};

}
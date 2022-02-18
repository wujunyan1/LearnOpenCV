#pragma once

#include "../render/ShaderProgram.h"

namespace OpenGL
{
	// ĳ��Shader��Ⱦ
	class ShaderGLProgram : public Render::ShaderProgram
	{
	public:

		void RenderMaterial(Render::Material* material);

		void SetVSAndPS(std::string vs, std::string ps);

	protected:

	};

}
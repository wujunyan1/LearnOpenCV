#pragma once

#include "../render/ShaderProgram.h"

namespace OpenGL
{
	// Ä³¸öShaderäÖÈ¾
	class ShaderGLProgram : public Render::ShaderProgram
	{
	public:

		void RenderMaterial(Render::Material* material);

		void SetVSAndPS(std::string vs, std::string ps);

	protected:

	};

}
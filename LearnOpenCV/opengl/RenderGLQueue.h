#pragma once

#include "OpenGLCore.h"
#include "../render/RenderQueue.h"

namespace OpenGL
{
	class RenderGLProgram : public Render::RenderProgram
	{
	public:
		RenderGLProgram();
	};

	class RenderGLQueue : public Render::RenderQueue
	{
	public:
		RenderGLQueue();
		~RenderGLQueue();

		void Render() {};
	private:

	};

}
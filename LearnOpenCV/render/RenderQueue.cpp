#include "RenderQueue.h"

namespace Render
{
	RenderProgram::RenderProgram()
	{
		mesh = NULL;
		material = NULL;
		shaderProgram = NULL;
		vbo = 0;
	}
}
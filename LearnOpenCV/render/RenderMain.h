#pragma once

#include <map>
#include "../math/Math.h"

namespace Render
{
	int CreateVBO();
	int CreateVAO();
	int CreateShader();

	void SetVertexAttribPointer(int vbo, int passageway, size_t typeSize, size_t dataSize, float* data);


	void RenderVBO(int vbo);
}
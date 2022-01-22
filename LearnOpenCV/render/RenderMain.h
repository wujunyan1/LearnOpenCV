#pragma once

#include <map>
#include "../math/Math.h"

namespace Render
{
	int CreateVBO();
	int CreateVAO();

	void SetVertexArray(int vbo, std::vector<Math::Triangle<Math::Vector3>> vertex,
		std::vector<Math::Triangle<Math::Vector3>> uv,
		std::vector<Math::Triangle<Math::Vector3>> normal);
}
#pragma once

#include "../math/Math.h"

namespace Render
{
	class RenderInterface
	{
	public:
		RenderInterface();
		~RenderInterface();

		virtual unsigned int CreateVBO();
		virtual unsigned int CreateVAO();

		virtual void SetVertexArray(int vbo, std::vector<Math::Triangle<Math::Vector3>> vertex,
			std::vector<Math::Triangle<Math::Vector3>> uv,
			std::vector<Math::Triangle<Math::Vector3>> normal);

	private:

	};
}
#pragma once
#include "Core.h"
#include "Component.h"
#include "../math/Math.h"

namespace Core
{
	class Mesh : public Component
	{
	public:
		Mesh();

		void addTriangle(Math::Triangle<Math::Vector3> t, Math::Triangle<Math::Vector4> color) {
			triangles.push_back(t);
			colors.push_back(color);
		}

		void Render();

	private:
		std::vector<Math::Triangle<Math::Vector3>> triangles;
		std::vector<Math::Triangle<Math::Vector4>> colors;
	};
}

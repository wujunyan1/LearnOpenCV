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

		void addTriangle(Math::Triangle t, Math::Triangle color) {
			triangles.push_back(t);
			colors.push_back(color);
		}

		void Render();

	private:
		std::vector<Math::Triangle> triangles;
		std::vector<Math::Triangle> colors;
	};
}

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

		void addTriangle(Math::Triangle t) {
			triangles.push_back(t);
		}

		void Render();

	private:
		std::vector<Math::Triangle> triangles;
	};
}

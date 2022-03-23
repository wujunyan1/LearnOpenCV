#pragma once
#include "Core.h"
#include "Component.h"
#include "../math/Math.h"
#include "../render/RenderMain.h"
#include "../meshModel/AModel.h"


namespace Core
{
	class Model : public Component
	{
	public:
		Model();

		void addTriangle(Math::Triangle<Math::Vector3> t, Math::Triangle<Math::Vector4> color) {
			triangles.push_back(t);
			colors.push_back(color);
		}

		void setModel(AModel* model);
		

		void bindRender();

		void Render();
	private:
		std::vector<Math::Triangle<Math::Vector3>> triangles;
		std::vector<Math::Triangle<Math::Vector4>> colors;

		// ²ÄÖÊ
		Render::RenderProgram* renderProgram = NULL;
	};
}

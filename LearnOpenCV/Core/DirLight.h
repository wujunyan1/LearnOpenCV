#pragma once
#include "Core.h"
#include "Component.h"
#include "../math/Math.h"
#include "../render/RenderMain.h"
#include "../meshModel/AModel.h"
#include "../render/BlendFunc.h"

namespace Core
{
	class DirLight : public Component
	{
	public:
		DirLight();

		void Render();

	private:

		Vector3 diffuse;
	};
}

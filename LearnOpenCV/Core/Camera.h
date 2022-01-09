#pragma once
#include "Core.h"
#include "Component.h"
#include "Transform.h"

namespace Core
{
	class Camera : public Component
	{
	public:
		Camera();

		Mat4 getViewMat4();
		Mat4 getPerspectiveMat4();

	private:
		Transform* transform;
	};
}

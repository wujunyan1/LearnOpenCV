#pragma once
#include "../Core/Core.h"
#include "../Core/Component.h"
#include "../Core/Object.h"
#include "../Core/Transform.h"
#include <vector>

using namespace Core;
namespace UI 
{
	class UITransform : public Transform
	{
	public:

		UITransform() : Transform() {
		}

	private:

		Math::Vector2T<Vector2> rect_position = {{0.5, 0.5}, {0.5, 0.5}};

		Vector2 size = {0, 0};
		Vector2 anchor = { 0.5, 0.5 };
	};
}

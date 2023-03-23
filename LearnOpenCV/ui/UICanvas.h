#pragma once
#include "../Core/Core.h"
#include "../Core/Component.h"
#include "../Core/Object.h"
#include "../Core/Transform.h"
#include <vector>

using namespace Core;
namespace UI 
{
	class UICanvas : public Component
	{
	public:

		UICanvas();

		virtual void Bind();

		virtual void Render();
	private:

		void updateUITransform(Vector2 size);

	};
}

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

		void setMainUI(bool b) { m_isMainUI = b; };
		bool getMainUI() { return m_isMainUI; };

	private:

		void updateUITransform(Vector2 size);

	private:
		bool m_isMainUI = false;
	};
}

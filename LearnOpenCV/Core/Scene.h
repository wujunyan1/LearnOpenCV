#pragma once
#include "Core.h"
#include "Component.h"

namespace Core
{
	class Scene : public Component
	{
	public:
		Scene();

		void Bind();
	};
}

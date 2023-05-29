#pragma once

#include "../../Core/Core.h"
#include "../../Core/Component.h"

namespace War
{
	class MapClient : public Core::GameComponent
	{
	public:
		virtual void Init();
	};
}
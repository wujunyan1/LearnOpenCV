#pragma once

#include "../../Core/Core.h"
#include "../../Core/Component.h"

#include "../../war/map/Map.h"
#include "../../Core/Model.h"

using namespace Core;

namespace War
{
	class MapClient : public Core::GameComponent
	{
	public:

	public:
		virtual void Init();
		virtual void Bind();

		void setMap(Map* map);

	private:
		Map* m_map;

		Model* m_model;
	};
}
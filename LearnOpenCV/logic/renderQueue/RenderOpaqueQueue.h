#pragma once

#include <map>
#include "../../math/Math.h"
#include "../../render/RenderQueue.h"

namespace Logic
{
	class RenderOpaqueQueue: public Render::RenderQueue
	{
	public:
		RenderOpaqueQueue() : Render::RenderQueue()
		{

		}

		~RenderOpaqueQueue();

		void Render();

		void addRenderProgram(Render::RenderProgram* renderProgram);

		void clear();

	private:

	};


}
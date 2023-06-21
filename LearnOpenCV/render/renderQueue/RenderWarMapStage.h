#pragma once

#include "../math/Math.h"

#include "../Core/Camera.h"

#include "RenderWarMapQueue.h"
#include "../Core/Object.h"
#include "RenderStage.h"

namespace Render
{
	class RenderUIStage;

	class RenderWarMapStage : public RenderStage
	{
		friend class RenderStageManager;
	public:
		RenderWarMapStage(unsigned int index);

		~RenderWarMapStage();

		virtual void render(Core::Camera* renderCamera);

	protected:

	protected:
	};
}
#pragma once

#include "../Core/Core.h"
#include <map>
#include "../math/Math.h"
#include "../ShaderProgram.h"
#include "../Material.h"
#include "../renderMesh/RenderMesh.h"
#include "../BlendFunc.h"

#include "../Core/Camera.h"
#include "../meshModel/AModel.h"
#include "RenderQueue.h"

namespace Render
{
	class RenderWarMapQueue : public RenderQueue
	{
	public:
		RenderWarMapQueue();
		~RenderWarMapQueue();

		virtual void Render(Core::Camera* camera);

		virtual void clear();

	protected:
		Math::Matrix4 ortho;
	};
}
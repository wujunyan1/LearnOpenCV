#pragma once

#include "../math/Math.h"

namespace Render
{
	class RenderBuffer
	{

	public:
		RenderBuffer(int w, int h);

		Math::Vector3* getRenderBuffer();
		Math::Vector3* getNextBuffer();

		void changeNext();

	private:
		Math::Vector3* renderBuff;
		Math::Vector3* nextBuff;
	};
}
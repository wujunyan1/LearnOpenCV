#include "RenderBuffer.h"
#include "../math/Vector3.h"

using namespace Render;
RenderBuffer::RenderBuffer(int w, int h) 
{
	renderBuff = new Math::Vector3[w * h];
	nextBuff = new Math::Vector3[w * h];
}

Math::Vector3* RenderBuffer::getRenderBuffer()
{
	return renderBuff;
}

Math::Vector3* RenderBuffer::getNextBuffer()
{
	return nextBuff;
}

void RenderBuffer::changeNext()
{
	Math::Swap(renderBuff, nextBuff);
}
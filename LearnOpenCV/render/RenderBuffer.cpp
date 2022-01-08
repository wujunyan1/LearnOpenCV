#include "RenderBuffer.h"
#include "../math/Vector3.h"

using namespace Render;
using namespace cv;

RenderBuffer* RenderBuffer::instance = nullptr;

RenderBuffer* RenderBuffer::init(int _w, int _h)
{
	RenderBuffer::instance = new RenderBuffer(_w, _h);
	return instance;
}

RenderBuffer::RenderBuffer(int _w, int _h): w(_w),h(_h)
{
	renderBuff = Mat(w, h, CV_8UC3);
	nextBuff = Mat(w, h, CV_8UC3);
}

Mat RenderBuffer::getRenderBuffer()
{
	return renderBuff;
}

Mat RenderBuffer::getNextBuffer()
{
	return nextBuff;
}

void RenderBuffer::changeNext()
{
	Math::Swap(renderBuff, nextBuff);
}

void RenderBuffer::setBackgroundColor(Math::Vector3 color)
{
	renderBuff = Scalar(color.x * UCHAR_MAX, color.y * UCHAR_MAX, color.z * UCHAR_MAX);
}
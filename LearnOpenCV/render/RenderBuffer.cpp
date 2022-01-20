#include "RenderBuffer.h"
#include "../math/Vector3.h"
#include "../math/Vector4.h"
#include "../math/Triangle.h"

using namespace Render;
using namespace cv;

RenderBuffer* RenderBuffer::instance = nullptr;

RenderBuffer* RenderBuffer::init(int _w, int _h)
{
	RenderBuffer::instance = new RenderBuffer(_w, _h);
	return instance;
}

RenderBuffer::RenderBuffer(int _w, int _h)
{
	w = _w;
	h = _h;
	renderBuff = Mat(h, w, CV_8UC3);
	nextBuff = Mat(h, w, CV_8UC3);

	zBuffer = std::vector<float>();
	for (size_t i = 0; i < h * w; i++)
	{
		zBuffer.push_back(10000000.0f);
	}
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
	for (size_t i = 0; i < h * w; i++)
	{
		zBuffer[i] = 10000000.0f;
	}
}

void RenderBuffer::setColor(int col, int row, Math::Vector3 color, float z)
{
	int index = col + (row * w) - 1;
	float oldZ = zBuffer[index];
	if (z < oldZ) {
		renderBuff.at<Vec3b>(row, col) = Vec3b(color.x * UCHAR_MAX, color.y * UCHAR_MAX, color.z * UCHAR_MAX);
		zBuffer[index] = z;
	}
}

void Render::RenderBuffer::swapRenderBuffers()
{

}

/**
	p1 p2 p3
	u  v  1-u-v

	p1 
	
**/


void RenderBuffer::renderTriangle(Math::Triangle<Math::Vector3> triangle, Math::Triangle<Math::Vector4> color)
{
	/*Math::Matrix4 trans = Math::Matrix4(
		1, 0, 0, 0.5,
		0, 1, 0, 0.5,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	Math::Matrix4 ss = Math::Matrix4(
		0.5, 0, 0, 0,
		0, 0.5, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
	
	Math::Matrix4 ss = Math::Matrix4(
		1, 0, 0, 0,
		0, -1, 0, 1,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	Math::Matrix4 ss = Math::Matrix4(
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
	
	*/

	Math::Matrix4 sk = Math::Matrix4(
		0.5 * w, 0, 0, 0.5 * w,
		0, -0.5 * h, 0, 0.5 * h,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	Math::Triangle<Math::Vector3> renderTriangle = Math::Triangle<Math::Vector3>();

	sk.printMat4();
	Math::Vector4 v1 = sk * Math::Vector4(triangle.points[0], 1.0f);
	Math::Vector4 v2 = sk * Math::Vector4(triangle.points[1], 1.0f);
	Math::Vector4 v3 = sk * Math::Vector4(triangle.points[2], 1.0f);

	renderTriangle.points[0] = Math::Vector3(sk * Math::Vector4(triangle.points[0], 1.0f));
	renderTriangle.points[1] = Math::Vector3(sk * Math::Vector4(triangle.points[1], 1.0f));
	renderTriangle.points[2] = Math::Vector3(sk * Math::Vector4(triangle.points[2], 1.0f));



	Math::Vector3 vl = renderTriangle.points[0];
	Math::Vector3 vr = renderTriangle.points[0];
	Math::Vector3 vd = renderTriangle.points[0];
	Math::Vector3 vt = renderTriangle.points[0];
	int minYIndex = 0;

	for (size_t i = 1; i < 3; i++)
	{
		Math::Vector3 v = renderTriangle.points[i];
		if (v.y < vd.y) {
			minYIndex = i;
			vd = v;
		}
		else if (v.y > vt.y) {
			vt = v;
		}
	}
	for (size_t i = 0; i < 3; i++)
	{
		if (i != minYIndex)
		{
			Math::Vector3 v = renderTriangle.points[i];
			if (v.x < vl.x) {
				vl = v;
			}
			else if (v.x >= vr.x) {
				vr = v;
			}
		}
	}


	/*for (size_t i = 1; i < 3; i++)
	{
		Math::Vector3 v = renderTriangle.points[i];

		if (v.y < vd.y) {
			if (vd.x < vl.x) {
				vl = vd;
			}
			if (vd.x > vr.x) {
				vr = vd;
			}

			vd = v;
		}
		else 
		{
			if (v.x <= vl.x) {
				vr = vl;
				vl = v;
			}
			else 
			{
				vr = v;
			}
		}

		if (v.y > vt.y)
		{
			vt = v;
		}
	}*/


	for (int y = Math::Max((int)vd.y, 0); y <= (int)vt.y && y < h; y++)
	{
		int minX = vd.x + (y - vd.y) * (vl.x - vd.x) / (vl.y - vd.y);
		int maxX = vd.x + (y - vd.y) * (vr.x - vd.x) / (vr.y - vd.y);

		minX = Math::Max(minX, 0);
		for (int x = minX; x <= maxX && x < w; x++) 
		{
			Math::Vector3 p = Math::Vector3(x, y, 0);
			if (renderTriangle.isIn(p)) {
				Math::Vector3 uv = renderTriangle.getUV(p);
				Math::Vector3 c = color.points[0] * uv.x + color.points[1] * uv.y + color.points[2] * uv.z;
				float z = renderTriangle.points[0].z * uv.x + renderTriangle.points[1].z * uv.y + renderTriangle.points[2].z * uv.z;

				setColor(x, y, c, z);
				//renderBuff.at<Vec3b>(y, x) = Vec3b(c.x * UCHAR_MAX, c.y * UCHAR_MAX, c.z * UCHAR_MAX);
			}
		}
	}


	/*int maxX = 0, maxY = 0;
	int minX = w, minY = h;

	for (size_t i = 0; i < 3; i++)
	{
		Math::Vector3 v = renderTriangle.points[i];

		maxX = Math::Max(maxX, (int)v.x);
		minX = Math::Min(minX, (int)v.x);
		maxY = Math::Max(maxY, (int)v.y);
		minY = Math::Min(minY, (int)v.y);

	}

	float area = renderTriangle.getArea();

	for (size_t col = minX; col <= maxX && col < w; col++)
	{
		for (size_t row = minY; row <= maxY && row < h; row++)
		{
			Math::Vector3 p = Math::Vector3(col, row, 0);
			if (renderTriangle.isIn(p)) {
				Math::Vector3 uv = renderTriangle.getUV(p);
				Math::Vector3 c = color.points[0] * uv.x + color.points[1] * uv.y + color.points[2] * uv.z;

				renderBuff.at<Vec3b>(row, col) = Vec3b(c.x * UCHAR_MAX, c.y * UCHAR_MAX, c.z * UCHAR_MAX);
			}
		}
	}*/
}

void RenderBuffer::renderTriangle(Math::Triangle<Math::Vector3> triangle, Math::Vector3 color)
{
	Math::Matrix4 sk = Math::Matrix4(
		0.5 * w, 0, 0, 0.5 * w,
		0, -0.5 * h, 0, 0.5 * h,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	Math::Triangle<Math::Vector3> renderTriangle;

	renderTriangle.points[0] = sk * Math::Vector4(triangle.points[0], 1.0f);
	renderTriangle.points[1] = sk * Math::Vector4(triangle.points[1], 1.0f);
	renderTriangle.points[2] = sk * Math::Vector4(triangle.points[2], 1.0f);



	int maxX = 0,maxY = 0;
	int minX = w, minY = h;

	for (size_t i = 0; i < 3; i++)
	{
		Math::Vector3 v = renderTriangle.points[i];

		maxX = Math::Max(maxX, (int)v.x);
		minX = Math::Min(minX, (int)v.x);
		maxY = Math::Max(maxY, (int)v.y);
		minY = Math::Min(minY, (int)v.y);
	}

	for (size_t col = minX; col <= maxX; col++)
	{
		for (size_t row = minY; row <= maxY; row++)
		{
			if (renderTriangle.isIn(Math::Vector3(col, row, 0))) {
				renderBuff.at<Vec3b>(row, col) = Vec3b(color.x * UCHAR_MAX, color.y * UCHAR_MAX, color.z * UCHAR_MAX);
			}
		}
	}
}
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

RenderBuffer::RenderBuffer(int _w, int _h)
{
	w = _w;
	h = _h;
	renderBuff = Mat(h, w, CV_8UC3);
	nextBuff = Mat(h, w, CV_8UC3);
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

void RenderBuffer::setColor(int col, int row, Math::Vector3 color)
{
	renderBuff.at<Vec3b>(row, col) = Vec3b(color.x * UCHAR_MAX, color.y * UCHAR_MAX, color.z * UCHAR_MAX);
}

/**
	p1 p2 p3
	u  v  1-u-v

	p1 
	
**/


void RenderBuffer::renderTriangle(Math::Triangle triangle, Math::Triangle color)
{
	Math::Matrix4 trans = Math::Matrix4(
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

	triangle.points[0] = trans * ss * Math::Vector4(triangle.points[0], 1.0f);
	triangle.points[1] = trans * ss * Math::Vector4(triangle.points[1], 1.0f);
	triangle.points[2] = trans * ss * Math::Vector4(triangle.points[2], 1.0f);

	triangle.points[0].y = 1 - triangle.points[0].y;
	triangle.points[1].y = 1 - triangle.points[1].y;
	triangle.points[2].y = 1 - triangle.points[2].y;

	Math::Triangle renderTriangle = triangle * Math::Vector3(w, h, 0);

	int maxX = 0, maxY = 0;
	int minX = w, minY = h;

	printf("============renderTriangle===============\n");
	printf("v0  == %f %f %f \n", triangle.points[0].x, triangle.points[0].y, triangle.points[0].z);
	printf("v1  == %f %f %f \n", triangle.points[1].x, triangle.points[1].y, triangle.points[1].z);
	printf("v2  == %f %f %f \n", triangle.points[2].x, triangle.points[2].y, triangle.points[2].z);


	printf("============renderPosTriangle===============\n");
	printf("v0  == %f %f %f \n", renderTriangle.points[0].x, renderTriangle.points[0].y, renderTriangle.points[0].z);
	printf("v1  == %f %f %f \n", renderTriangle.points[1].x, renderTriangle.points[1].y, renderTriangle.points[1].z);
	printf("v2  == %f %f %f \n", renderTriangle.points[2].x, renderTriangle.points[2].y, renderTriangle.points[2].z);

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
	}
}

void RenderBuffer::renderTriangle(Math::Triangle triangle, Math::Vector3 color)
{
	triangle.points[0].y = 1.0f - triangle.points[0].y;
	triangle.points[1].y = 1.0f - triangle.points[1].y;
	triangle.points[2].y = 1.0f - triangle.points[2].y;

	Math::Triangle renderTriangle = triangle * Math::Vector3(w, h, 0);

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
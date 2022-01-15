#pragma once

#include "../math/Math.h"
#include "../math/Triangle.h"
#include <opencv2/opencv.hpp>

using namespace cv;

namespace Render
{
	class RenderBuffer
	{

	public:
		static RenderBuffer* init(int _w, int _h);
		static RenderBuffer getInstance() { return *instance; };

		Mat getRenderBuffer();
		Mat getNextBuffer();

		void changeNext();

		void setBackgroundColor(Math::Vector3 color);

		void renderTriangle(Math::Triangle<Math::Vector3> triangle, Math::Vector3 color);
		void renderTriangle(Math::Triangle<Math::Vector3> triangle, Math::Triangle<Math::Vector4> color);

		void setColor(int col, int row, Math::Vector3 color);

		void swapRenderBuffers();

	private:


	private:
		RenderBuffer(int _w, int _h);

		Mat renderBuff;
		Mat nextBuff;

		unsigned int w, h;

		std::vector<Math::Triangle<Math::Vector3>> renderTriangles;
		std::vector<Math::Triangle<Math::Vector4>> renderColor;

		static RenderBuffer* instance;
	};
}
#pragma once

#include "../math/Math.h"
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

	private:
		RenderBuffer(int _w, int _h);

		Mat renderBuff;
		Mat nextBuff;

		unsigned int w, h;

		static RenderBuffer* instance;
	};
}
#include "Main.h"

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include "render/RenderBuffer.h"

#include "math/Vector3.h"

using namespace Render;
using namespace cv;

int main(int argc, char* argv[])
{
	bool isClose = true;

	int w = 700;
	int h = 700;
	RenderBuffer* buffer = RenderBuffer::init(w, h);
	buffer->setBackgroundColor(Math::Vector3(0.0f, 0.0f, 0.02f));

	while (isClose) {
		cv::Mat image = buffer->getRenderBuffer();
		//image.convertTo(image, CV_8UC3, 1.0f);
		cv::imshow("image", image);
		int key = cv::waitKey(10);
	}

	return 0;
}
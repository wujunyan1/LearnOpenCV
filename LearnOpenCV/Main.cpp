#include "Main.h"

#include <opencv2/opencv.hpp>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	bool isClose = true;

	while (isClose) {
		cv::Mat image(700, 700, CV_32FC3);
		image.convertTo(image, CV_8UC3, 1.0f);
		cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
		cv::imshow("image", image);
		int key = cv::waitKey(10);
	}

	return 0;
}
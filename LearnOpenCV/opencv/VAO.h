#pragma once

#include <opencv2/opencv.hpp>

using namespace cv;

namespace OpenCV
{
	class VAO
	{
	public:
		VAO()
		{
			_vaild = true;
		}

		bool isVaild()
		{
			return _vaild;
		}

		void delate()
		{
			_vaild = false;
		}

	private:
		bool _vaild;
	};

	class VAOManager
	{
	public:
		static int createVAO();

	private:
		static int _vao_index;
		static std::vector<VAO*>* vaos;
	};
}
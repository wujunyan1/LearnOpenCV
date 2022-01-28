#pragma once

#include <opencv2/opencv.hpp>
#include "../math/Math.h"

using namespace cv;

namespace OpenCV
{
	class CVShader
	{
	public:
		CVShader()
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
		Math::Matrix4 mvp;

	private:
		bool _vaild;
	};

	class CVShaderManager
	{
	public:
		static int createCVShader();

	private:
		static int _shader_index;
		static std::vector<CVShader*>* shaders;
	};
}
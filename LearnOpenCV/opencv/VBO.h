#pragma once

#include <opencv2/opencv.hpp>
#include "../math/Math.h"

using namespace cv;

namespace OpenCV
{
	struct VBOData
	{
		size_t typeSize;
		std::vector<Math::Vector1>* datas;
	};

	class VBO
	{
	public:
		VBO()
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

		void SetVertexAttribPointer(int passageway, size_t typeSize, size_t dataSize, float* data);

	private:
		Math::Vector1 getDataType(size_t dataSize, float* data);

	private:
		bool _vaild;

		VBOData datas[16] = {};
	};

	class VBOManager
	{
	public:
		static int createVBO();

		static void SetVertexAttribPointer(int vbo, int passageway, size_t typeSize, size_t dataSize, float* data);

	private:
		static int _vbo_index;
		static std::vector<VBO*>* vbos;
	};
}
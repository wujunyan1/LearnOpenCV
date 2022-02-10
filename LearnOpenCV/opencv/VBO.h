#pragma once

#include <opencv2/opencv.hpp>
#include "../math/Math.h"
#include "../render/RenderMain.h"

using namespace cv;
using namespace Render;

namespace OpenCV
{
	struct VBOData
	{
		Render::ShaderParamType typeSize;
		std::vector<void*>* datas;
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

		void SetVertexAttribPointer(int passageway, Render::ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data);

	private:
		void* getDataType(Render::ShaderParamType typeSize, void* data);

	private:
		bool _vaild;

		VBOData datas[16] = {};
	};

	class VBOManager
	{
	public:
		static int createVBO();

		static void SetVertexAttribPointer(int vbo, int passageway, Render::ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data);

	private:
		static int _vbo_index;
		static std::vector<VBO*>* vbos;

		static void* currCatchData;
	};
}
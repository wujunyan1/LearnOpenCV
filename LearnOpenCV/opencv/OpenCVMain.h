#pragma once

#include <opencv2/opencv.hpp>
#include "../render/RenderMain.h"
#include "RenderBuffer.h"

using namespace cv;

namespace OpenCV
{

	unsigned int CreateVBO();


	unsigned int CreateVAO();

	void SetVertexAttribPointer(int vbo, int passageway, Render::ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data);

	unsigned int CreateShader();


	void InitEngine();
	int CreateWindow(int w, int h, std::string title);
	void ClearBuffer();

	void SetBackgroundColor(Math::Vector3 color);

	static RenderBuffer* buffer = NULL;
}
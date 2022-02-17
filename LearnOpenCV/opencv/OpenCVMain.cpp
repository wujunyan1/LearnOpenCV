#include "OpenCVMain.h"
#include "../render/RenderMain.h"
#include "VBO.h"
#include "VAO.h"
#include "CVShader.h"
#include <opencv2/opencv.hpp>
#include "RenderBuffer.h"

using namespace cv;

using namespace Render;

namespace OpenCV
{
	unsigned int CreateVBO()
	{
		return VBOManager::createVBO();
	}


	unsigned int CreateVAO()
	{
		return VAOManager::createVAO();
	}

	void SetVertexAttribPointer(int vbo, int passageway, Render::ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data)
	{
		VBOManager::SetVertexAttribPointer(vbo, passageway, typeSize, dataSize, dataLength, data);
	}

	unsigned int CreateShader()
	{
		return CVShaderManager::createCVShader();
	}


	void InitEngine()
	{

	}

	int CreateWindow(int w, int h, std::string title)
	{
		buffer = RenderBuffer::init(w, h);
		buffer->setBackgroundColor(Math::Vector3(0.0f, 0.0f, 0.6f));
		buffer->setAntiAliasing(AntiAliasing::X2);

		return 0;
	}

	void ClearBuff()
	{

	}

	void SetBackgroundColor(Math::Vector3 color)
	{
		buffer->setBackgroundColor(color);
	}
}

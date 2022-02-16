#include "OpenCVMain.h"
#include "../render/RenderMain.h"
#include "VBO.h"
#include "VAO.h"
#include "CVShader.h"

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
}

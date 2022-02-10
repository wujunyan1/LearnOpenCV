#include "OpenCVMain.h"
#include "../render/RenderMain.h"
#include "VBO.h"
#include "VAO.h"
#include "CVShader.h"

using namespace OpenCV;
using namespace cv;

using namespace Render;

int Render::CreateVBO()
{
	return VBOManager::createVBO();
}


int Render::CreateVAO()
{
	return VAOManager::createVAO();
}

void Render::SetVertexAttribPointer(int vbo, int passageway, Render::ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data)
{
	VBOManager::SetVertexAttribPointer(vbo, passageway, typeSize, dataSize, dataLength, data);
}

int Render::CreateShader()
{
	return CVShaderManager::createCVShader();
}
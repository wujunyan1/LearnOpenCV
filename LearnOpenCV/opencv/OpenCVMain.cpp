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

void Render::SetVertexAttribPointer(int vbo, int passageway, size_t typeSize, size_t dataSize, float* data)
{
	VBOManager::SetVertexAttribPointer(vbo, passageway, typeSize, dataSize, data);
}

int Render::CreateShader()
{
	return CVShaderManager::createCVShader();
}
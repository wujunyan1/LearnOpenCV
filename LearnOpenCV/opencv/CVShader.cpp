#include "OpenCVMain.h"
#include "CVShader.h"

using namespace OpenCV;
using namespace cv;



int CVShaderManager::_shader_index = 0;
std::vector<CVShader*>* CVShaderManager::shaders = new std::vector<CVShader*>();

int CVShaderManager::createCVShader()
{
	CVShader* vbo = new CVShader();

	if (_shader_index >= shaders->size())
	{
		shaders->resize(shaders->size() + 10);
	}

	int returnIndex = _shader_index;
	(*shaders)[_shader_index] = vbo;

	size_t s = shaders->size();
	_shader_index += 1;
	for (size_t i = _shader_index; i < s; i++)
	{
		CVShader* _vbo = shaders->at(i);
		if (_vbo && _vbo->isVaild())
		{
			_shader_index = i + 1;
		}
		else
		{
			break;
		}
	}

	return returnIndex;
}
#include "OpenCVMain.h"
#include "VAO.h"

using namespace OpenCV;
using namespace cv;

int VAOManager::_vao_index = 0;
std::vector<VAO*>* VAOManager::vaos = new std::vector<VAO*>();

int VAOManager::createVAO()
{
	VAO* vao = new VAO();

	if (_vao_index >= vaos->size())
	{
		vaos->resize(vaos->size() + 10);
	}

	int returnIndex = _vao_index;
	(*vaos)[_vao_index] = vao;

	size_t s = vaos->size();
	_vao_index += 1;
	for (size_t i = _vao_index; i < s; i++)
	{
		VAO* _vao = vaos->at(i);
		if (_vao && _vao->isVaild())
		{
			_vao_index = i + 1;
		}
		else
		{
			break;
		}
	}

	return returnIndex;
}
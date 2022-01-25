#include "OpenCVMain.h"
#include "VBO.h"

using namespace OpenCV;
using namespace cv;


Math::Vector1 VBO::getDataType(size_t dataSize, float* data)
{
	switch (dataSize)
	{
	case 1:
		return Math::Vector1(*data++);
	case 2:
		return Math::Vector2(*data++, *data++);
	case 3:
		return Math::Vector3(*data++, *data++, *data++);
	case 4:
		return Math::Vector4(*data++, *data++, *data++, *data++);
	default:
		break;
	}
}

void VBO::SetVertexAttribPointer(int passageway, size_t typeSize, size_t dataSize, float* data)
{
	VBOData vboData = datas[passageway];
	vboData.typeSize = typeSize;
	if (vboData.datas != nullptr) {
		vboData.datas->clear();
	}
	else {
		vboData.datas = new std::vector<Math::Vector1>();
	}

	for (size_t i = 0; i < dataSize;)
	{
		Math::Vector1 v = getDataType(typeSize, data);

		i += typeSize;

		vboData.datas->push_back(v);
	}
}



int VBOManager::_vbo_index = 0;
std::vector<VBO*>* VBOManager::vbos = new std::vector<VBO*>();

int VBOManager::createVBO()
{
	VBO* vbo = new VBO();

	if (_vbo_index >= vbos->size())
	{
		vbos->resize(vbos->size() + 10);
	}

	int returnIndex = _vbo_index;
	(*vbos)[_vbo_index] = vbo;

	size_t s = vbos->size();
	_vbo_index += 1;
	for (size_t i = _vbo_index; i < s; i++)
	{
		VBO* _vbo = vbos->at(i);
		if (_vbo && _vbo->isVaild())
		{
			_vbo_index = i + 1;
		}
		else
		{
			break;
		}
	}

	return returnIndex;
}

void VBOManager::SetVertexAttribPointer(int vbo, int passageway, size_t typeSize, size_t dataSize, float* data)
{
	VBO* _vbo = vbos->at(vbo);
	_vbo->SetVertexAttribPointer(passageway, typeSize, dataSize, data);
}
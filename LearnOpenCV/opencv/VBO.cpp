#include "OpenCVMain.h"
#include "VBO.h"
#include "../render/RenderMain.h"

using namespace OpenCV;
using namespace cv;


void* VBO::getDataType(Render::ShaderParamType typeSize, void* data)
{
	switch (typeSize)
	{
	case Render::SPT_UNKNOWN:
		return 0;
		break;
	case Render::SPT_INT:
		return (int*)data;
		break;
	case Render::SPT_FLOAT:
		break;
	case Render::SPT_VEC2:
		break;
	case Render::SPT_VEC3:
		break;
	case Render::SPT_VEC4:
		break;
	case Render::SPT_MAT4:
		break;
	case Render::SPT_TEXTURE:
		break;
	default:
		break;
	}

	switch (dataSize)
	{
	case 1:
		return &Math::Vector1(*data++);
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

void VBO::SetVertexAttribPointer(int passageway, Render::ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data)
{
	VBOData vboData = datas[passageway];
	vboData.typeSize = typeSize;
	if (vboData.datas != nullptr) {
		vboData.datas->clear();
	}
	else {
		vboData.datas = new std::vector<void*>();
	}

	for (size_t i = 0; i < dataLength;)
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

void VBOManager::SetVertexAttribPointer(int vbo, int passageway, Render::ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data)
{
	VBO* _vbo = vbos->at(vbo);
	_vbo->SetVertexAttribPointer(passageway, typeSize, dataSize, dataLength, data);
}
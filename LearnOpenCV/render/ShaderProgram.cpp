#include "ShaderProgram.h"
#include "Material.h"

namespace Render
{
	ShaderParam::ParamData::ParamData()
	{
		
	}

	ShaderParam::ParamData::ParamData(const ParamData& other)
	{
		copySize = other.copySize;
		if (copySize)
		{
			auto temp = malloc(copySize);
			memcpy(temp, other.data, copySize);
			data = temp;
		}
		else
		{
			data = other.data;
		}
	}

	ShaderParam::ParamData::ParamData(ParamData&& other) noexcept
	{
		data = other.data;
		copySize = other.copySize;
		other.data = nullptr;
		other.copySize = 0;
	}

	ShaderParam::ParamData& ShaderParam::ParamData::operator=(ParamData other) noexcept
	{
		std::swap(data, other.data);
		std::swap(copySize, other.copySize);
		return *this;
	}

	ShaderParam::ParamData::~ParamData()
	{
		if (data && copySize)
			::free((void*)data);
	}

	void ShaderParam::ParamData::setData(const void* data, int copySize)
	{
		reset();
		if (copySize)
		{
			auto temp = malloc(copySize);
			memcpy(temp, data, copySize);
			this->copySize = copySize;
			this->data = temp;
		}
		else
		{
			this->copySize = 0;
			this->data = data;
		}
	}

	void ShaderParam::ParamData::reset()
	{
		*this = {};
	}
}
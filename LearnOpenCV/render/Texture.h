#pragma once

#include "../math/Math.h"
#include "../file/Image.h"

namespace Render
{
	struct Texture
	{
		Core::Image* image;
		std::string imageName;
		std::string uniformName;
	};
}
#pragma once

#include <string>
#include "Image.h"

class ImageLoad
{
public:
	static Image* LoadImage(std::string path);
};


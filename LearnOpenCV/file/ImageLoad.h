#pragma once

#include <string>
#include <map>
#include "Image.h"

namespace Core
{
	class ImageLoad
	{
	private:
		static std::map<std::string, Image*>* image_ids;

	public:
		static Image* LoadImage(std::string path);

		static Image* GetImage(std::string path);
	};
}


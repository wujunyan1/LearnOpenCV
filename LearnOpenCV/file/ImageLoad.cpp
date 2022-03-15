#include "ImageLoad.h"
#include "FilePathManager.h"

#include "stb_image.h"

#include "../render/RenderMain.h"

using namespace Core;

std::map<std::string, Image*>* ImageLoad::image_ids = new std::map<std::string, Image*>();

Image* ImageLoad::LoadImage(std::string path)
{
	auto it = image_ids->find(path);
	if (it != image_ids->end())
	{
		return it->second;
	}

	stbi_set_flip_vertically_on_load(true);

	std::string s = std::string(FilePathManager::getRootPath());

	int width, height, nrChannels;
	unsigned char* data = stbi_load((s + path).c_str(), &width, &height, &nrChannels, 0);

	Image* image = NULL;
	if (data)
	{
		image = Render::CreateImage(width, height, nrChannels, data);
	}
	stbi_image_free(data);

	image_ids->insert(std::pair<std::string, Image*>(path, image));
	return image;
}
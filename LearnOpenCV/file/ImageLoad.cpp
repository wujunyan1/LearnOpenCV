#include "ImageLoad.h"
#include "FilePathManager.h"

#include "stb_image.h"

Image* ImageLoad::LoadImage(std::string path)
{
	stbi_set_flip_vertically_on_load(true);

	std::string s = std::string(FilePathManager::getRootPath());

	int width, height, nrChannels;
	unsigned char* data = stbi_load((s + path).c_str(), &width, &height, &nrChannels, 0);

	Image* image = NULL;
	if (data)
	{
		image = new Image(width, height, nrChannels, data);
	}
	stbi_image_free(data);
	return image;
}
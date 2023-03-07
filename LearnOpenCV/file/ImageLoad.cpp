#include "ImageLoad.h"
#include "FilePathManager.h"

#include "stb_image.h"
#include "stb_image_write.h"

#include "../render/RenderMain.h"

using namespace Core;

std::map<std::string, Image*>* ImageLoad::image_ids = new std::map<std::string, Image*>();


Image* ImageLoad::LoadImageByMemory(const std::string& path, const aiTexture* texture)
{
	unsigned char* image_data = nullptr;
	int width, height, channels;
	if (texture->mHeight == 0) {
	    // mHeight = 0 means embedded textures inside
	    // here we use stb to save texture images
		image_data = stbi_load_from_memory(
			reinterpret_cast<unsigned char*>(texture->pcData),
	        texture->mWidth, &width, &height, &channels, 0);

	    std::string filename = path + ".jpg";
	    if (texture->mFilename.length > 0) {
	        filename = path + std::string(texture->mFilename.data) + ".jpg";
	    }

		/*std::string s = std::string(FilePathManager::getRootPath());
		int result = stbi_write_jpg((s + filename).c_str(), width, height, channels, image_data, 100);
		printf("save write %d image %s \n", result, (s + filename).c_str());*/
		Image* image = new Image2D(filename, width, height, channels, image_data);
		image_ids->insert(std::pair<std::string, Image*>(path, image));
		return image;
	}

	return nullptr;
}

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
		image = new Image2D(path, width, height, nrChannels, data);
	}
	stbi_image_free(data);

	image_ids->insert(std::pair<std::string, Image*>(path, image));
	return image;
}

Image* Core::ImageLoad::GetImage(std::string& path)
{
	auto it = image_ids->find(path);
	if (it != image_ids->end())
	{
		return it->second;
	}
	return nullptr;
}

ImageCubeMap* ImageLoad::CreateImageCubeMap(std::string& name, std::vector<std::string>& faces)
{
	Image* image = GetImage(name);
	if (image)
	{
		ImageCubeMap* map = dynamic_cast<ImageCubeMap*>(image);
		if (map)
		{
			return map;
		}
	}
	ImageCubeMap* map = new ImageCubeMap(name, faces);
	image_ids->insert(std::pair<std::string, Image*>(name, map));
	return map;
}

void ImageLoad::DestroyImage(Image* image)
{
	auto it = image_ids->find(image->getName());
	if (it != image_ids->end())
	{
		delete it->second;
		image_ids->erase(image->getName());
	}
	else
	{
		delete image;
	}
}

void ImageLoad::Destroy()
{
	for (auto it = image_ids->begin(); it != image_ids->end(); it++)
	{
		Image* image = it->second;
		delete image;
	}
	image_ids->clear();
}
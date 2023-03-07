#pragma once

#include <string>
#include <map>
#include <vector>
#include "Image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Core
{
	class ImageLoad
	{
	private:
		static std::map<std::string, Image*>* image_ids;

	public:
		static Image* LoadImageByMemory(const std::string& path, const aiTexture* texture);

		static Image* LoadImage(std::string path);

		static Image* GetImage(std::string& path);

		static ImageCubeMap* CreateImageCubeMap(std::string& name, std::vector<std::string>& faces);

		static void DestroyImage(Image* image);

		static void Destroy();
	};
}


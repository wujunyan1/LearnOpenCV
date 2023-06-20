#include "Image.h"

#include "stb_image.h"
#include "stb_image_write.h"

#include "FilePathManager.h"

using namespace Core;

const int Image::textureIndex[32] = {
	GL_TEXTURE0,
	GL_TEXTURE1,
	GL_TEXTURE2,
	GL_TEXTURE3,
	GL_TEXTURE4,
	GL_TEXTURE5,
	GL_TEXTURE6,
	GL_TEXTURE7,
	GL_TEXTURE8,
	GL_TEXTURE9,
	GL_TEXTURE10,
	GL_TEXTURE11,
	GL_TEXTURE12,
	GL_TEXTURE13,
	GL_TEXTURE14,
	GL_TEXTURE15,
	GL_TEXTURE16,
	GL_TEXTURE17,
	GL_TEXTURE18,
	GL_TEXTURE19,
	GL_TEXTURE20,
	GL_TEXTURE21,
	GL_TEXTURE22,
	GL_TEXTURE23,
	GL_TEXTURE24,
	GL_TEXTURE25,
	GL_TEXTURE26,
	GL_TEXTURE27,
	GL_TEXTURE28,
	GL_TEXTURE29,
	GL_TEXTURE30,
	GL_TEXTURE31
};

ImageCubeMap::ImageCubeMap(std::string & name, std::vector<std::string>&faces) :Image(name, Image::IMAGE_TYPE::TEXTURE_CUBE_MAP)
{
	this->name = name;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	std::string s = std::string(FilePathManager::getRootPath());
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load((s + faces[i]).c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

Core::ImageFont::ImageFont(std::string& name, unsigned int textureID) :Image(name, Image::IMAGE_TYPE::TEXTURE_2D)
{
	this->textureID = textureID;
}


Core::ImageAtlasPlot::ImageAtlasPlot(std::string name, Image* atlas, float x, float y, float width, float height, bool isNormal) :Image(name, Image::IMAGE_TYPE::TEXTURE_2D)
{
	m_atlas = atlas;
	m_x = x;
	m_y = y;
	m_w = width;
	m_h = height;
	if (!isNormal)
	{
		m_w = height;
		m_h = width;
	}
}

Core::ImageCustom::ImageCustom(std::string name, int width, int height):Image(name, Image::IMAGE_TYPE::TEXTURE_2D)
{
	this->name = name;
	this->width = width;
	this->height = height;
	this->nrChannels = 4;

	printf("%x\n", nrChannels);
	glGenTextures(1, &textureID); // ¥¥Ω®Œ∆¿Ì

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Core::ImageCustom::setTextureData(int x, int y, int w, int h, void* data)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		x,
		y,
		w,
		h,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data
	);
	glBindTexture(GL_TEXTURE_2D, 0);
}

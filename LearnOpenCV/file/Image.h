#pragma once
#include <iostream>
#include <GL/glew.h>
#include <vector>

namespace Core
{
	class Image
	{
	public:
		enum IMAGE_TYPE
		{
			TEXTURE_2D = GL_TEXTURE_2D,
			TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
		};

	public:
		Image(std::string& name, IMAGE_TYPE type)
		{
			this->name = name;
			m_type = type;
		}

		~Image()
		{
			glDeleteTextures(1, &textureID);
		}


		virtual void use(int textureIndex)
		{
			//glDepthMask(GL_FALSE);                                                         //关掉深度测试     
			//glEnable(GL_BLEND);                                                            //开混合模式贴图     
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                             //设置混合方式 
			//GL_ZERO

			//GL_BLEND

			glActiveTexture(Image::textureIndex[textureIndex]);
			glBindTexture(GL_TEXTURE_2D, textureID);
			//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);			//贴图模式为混合
		}

		void exit(int textureIndex)
		{

		}

		const unsigned int getTextureId() { return textureID; };
		const std::string& getName() { return name; };

		void setBlendFunc();

	public:
		static const int textureIndex[32];

	protected:
		std::string name;
		IMAGE_TYPE m_type;

		unsigned int textureID;
		int width, height, nrChannels;
	};


	class Image2D : public Image
	{
	public:
		Image2D(std::string& path, int width, int height, int nrChannels, unsigned char* data):Image(path, Image::IMAGE_TYPE::TEXTURE_2D)
		{
			this->name = path;
			this->width = width;
			this->height = height;
			this->nrChannels = nrChannels;

			printf("%x\n", nrChannels);
			glGenTextures(1, &textureID); // 创建纹理

			glBindTexture(GL_TEXTURE_2D, textureID);

			/*GL_NEAREST_MIPMAP_NEAREST
			使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样
			GL_LINEAR_MIPMAP_NEAREST
			使用最邻近的多级渐远纹理级别，并使用线性插值进行采样
			GL_NEAREST_MIPMAP_LINEAR
			在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
			GL_LINEAR_MIPMAP_LINEAR
			在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样*/

			//// 为当前绑定的纹理对象设置环绕、过滤方式
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			switch (nrChannels)
			{
			case 3:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				break;
			case 4:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				break;
			default:
				break;
			}
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		virtual void use(int textureIndex)
		{
			//glDepthMask(GL_FALSE);                                                         //关掉深度测试     
			//glEnable(GL_BLEND);                                                            //开混合模式贴图     
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                             //设置混合方式 
			//GL_ZERO

			//GL_BLEND

			glBindTexture(GL_TEXTURE_2D, textureID);
			glActiveTexture(Image::textureIndex[textureIndex]);
			//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);			//贴图模式为混合
		}

	};

	class ImageCubeMap : public Image
	{
	public:
		ImageCubeMap(std::string& name, std::vector<std::string>& faces);

		virtual void use(int textureIndex)
		{

			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
			glActiveTexture(Image::textureIndex[textureIndex]);
		}

	private:
	};

	class ImageFont : public Image
	{
	public:
		ImageFont(std::string& name, unsigned int textureID);

		virtual void use(int textureIndex)
		{
			glBindTexture(GL_TEXTURE_2D, textureID);
			glActiveTexture(Image::textureIndex[textureIndex]);
		}

	private:
	};
}
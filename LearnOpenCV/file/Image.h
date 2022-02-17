#pragma once
#include <iostream>
#include <GL/glew.h>

class Image
{

public:
	Image(int width, int height, int nrChannels, unsigned char* data) :width(width), height(height), nrChannels(nrChannels)
	{
		printf("%x\n", nrChannels);
		glGenTextures(1, &texture); // 创建纹理

		glBindTexture(GL_TEXTURE_2D, texture);

			/*GL_NEAREST_MIPMAP_NEAREST
			使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样
			GL_LINEAR_MIPMAP_NEAREST
			使用最邻近的多级渐远纹理级别，并使用线性插值进行采样
			GL_NEAREST_MIPMAP_LINEAR
			在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
			GL_LINEAR_MIPMAP_LINEAR
			在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样*/

		//// 为当前绑定的纹理对象设置环绕、过滤方式
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

	void use(int textureIndex) 
	{
		//glDepthMask(GL_FALSE);                                                         //关掉深度测试     
		glEnable(GL_BLEND);                                                            //开混合模式贴图     
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                             //设置混合方式 

		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(Image::textureIndex[textureIndex]);
		//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);			//贴图模式为混合
	}

public:
	static const int textureIndex[32];

private:

	int width, height, nrChannels;
	unsigned int texture;
};


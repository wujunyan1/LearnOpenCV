#pragma once

#include <map>
#include "../../math/Math.h"
#include "../../file/Image.h"
#include "../RenderFont.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

namespace Render
{

	class FontSource
	{
		friend class FontManager;

	public:
		struct Character {
			unsigned int     TextureID;  // 字形纹理的ID
			Math::Vector2T<unsigned int> Size;       // 字形大小
			Math::Vector2T<int> Bearing;    // 从基准线到字形左部/顶部的偏移值
			long     Advance;    // 原点距下一个字形原点的距离

			unsigned int uv;
		};

	public:
		FontSource(std::string font);
		~FontSource();

		Character getChar(char character);
		unsigned int getFontSize() {
			return fontSize;
		};

		Core::Image* getImage() {
			return image;
		};

		unsigned int getImageWidth()
		{
			return 256 * fontSize;
		}

	private:
		void updateCharacterTexture();

	private:
		std::string fontName;
		std::map<char, Character> Characters;

		FT_Library ft;
		FT_Face face;

		unsigned int fontSize = 48;

		unsigned char* textureBuff;

		Core::Image* image;
		unsigned int characterNum = 0;

		unsigned int texturesCharacterNum = 0;
		std::vector<char> needAddTextures;
	};


	class FontManager
	{
		FontManager();
	public:

		static FontSource* getFontSource(std::string font);

		static FontManager* GetInstance() {
			if (instance == nullptr) {
				instance = new FontManager();
			}

			return instance;
		}


		void checkCharacterTexture();
	private:

		void updateCharacterTexture(FontSource* source);
	private:

		static std::map<std::string, FontSource*> sources;
		static FontManager* instance;

	private:
		unsigned int fbo;
	};

}
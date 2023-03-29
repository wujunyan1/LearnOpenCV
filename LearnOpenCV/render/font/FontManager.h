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

		struct Character {
			unsigned int     TextureID;  // 字形纹理的ID
			Math::Vector2T<unsigned int> Size;       // 字形大小
			Math::Vector2T<int> Bearing;    // 从基准线到字形左部/顶部的偏移值
			long     Advance;    // 原点距下一个字形原点的距离
		};

	public:
		FontSource(std::string font);
		~FontSource();

		Character getChar(char character);
	private:
		void updateCharacterTexture();

	private:
		std::string fontName;
		std::map<char, Character> Characters;

		FT_Library ft;
		FT_Face face;

		unsigned char* textureBuff;
	};


	class FontManager
	{
	public:

		FontSource* getFontSource(std::string font);

	private:

		static std::map<std::string, FontSource*> sources;
	};

}
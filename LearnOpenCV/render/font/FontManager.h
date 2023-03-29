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
			unsigned int     TextureID;  // ���������ID
			Math::Vector2T<unsigned int> Size;       // ���δ�С
			Math::Vector2T<int> Bearing;    // �ӻ�׼�ߵ�������/������ƫ��ֵ
			long     Advance;    // ԭ�����һ������ԭ��ľ���
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
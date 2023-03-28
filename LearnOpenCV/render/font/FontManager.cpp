#include "FontManager.h"
#include "../../file/FilePathManager.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

namespace Render
{
	FontSource::FontSource(std::string font)
	{
		fontName = font;

		if (FT_Init_FreeType(&ft))
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;


		std::string s = std::string(FilePathManager::getRootPath());
		if (FT_New_Face(ft, (s + font).c_str(), 0, &face))
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
        for (GLubyte c = 0; c < 128; c++)
        {
            // 加载字符的字形 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // 生成纹理
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // 设置纹理选项
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // 储存字符供之后使用
            Character character = {
                texture,
                {face->glyph->bitmap.width, face->glyph->bitmap.rows},
                {face->glyph->bitmap_left, face->glyph->bitmap_top},
                face->glyph->advance.x
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
	}

    FontSource::~FontSource()
    {
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    FontSource::Character FontSource::getChar(char character)
    {
        auto it = Characters.find(character);
        if (it != Characters.end())
        {
            return it->second;
        }

        // 加载字符的字形 
        if (FT_Load_Char(face, character, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            return FontSource::Character();
        }
        // 生成纹理
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // 设置纹理选项
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 储存字符供之后使用
        Character characterResult = {
            texture,
            {face->glyph->bitmap.width, face->glyph->bitmap.rows},
            {face->glyph->bitmap_left, face->glyph->bitmap_top},
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(character, characterResult));

        return characterResult;
    }


    std::map<std::string, FontSource*> FontManager::sources = std::map<std::string, FontSource*>();
    FontSource* FontManager::getFontSource(std::string font)
    {
        auto it = sources.find(font);
        if (it != sources.end())
        {
            return it->second;
        }
        FontSource* source = new FontSource(font);
        sources.insert(std::pair<std::string, FontSource*>(font, source));

        return source;
    }
}
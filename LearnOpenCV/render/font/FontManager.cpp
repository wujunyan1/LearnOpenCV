#include "FontManager.h"
#include "../../file/FilePathManager.h"

#include "../render/RenderUIMesh.h"
#include "../meshModel/AUIMesh.h"

#include "../opengl/GLShader.h"
#include "../opengl/GLShaderManager.h"

#include "../render/RenderMain.h"

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

		FT_Set_Pixel_Sizes(face, 0, fontSize);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
        GLubyte c = 0;

        // 加载字符的字形 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        }
        // 生成纹理
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
            Math::Vector2T<unsigned int>(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            {face->glyph->bitmap_left, face->glyph->bitmap_top},
            face->glyph->advance.x,
            0,
        };
        Characters.insert(std::pair<char, Character>(c, character));
        texturesCharacterNum = characterNum = 1;
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
        //GLuint texture;
        //glGenTextures(1, &texture);
        //glBindTexture(GL_TEXTURE_2D, texture);
        //glTexImage2D(
        //    GL_TEXTURE_2D,
        //    0,
        //    GL_RED,
        //    face->glyph->bitmap.width,
        //    fontSize,
        //    0,
        //    GL_RED,
        //    GL_UNSIGNED_BYTE,
        //    face->glyph->bitmap.buffer
        //);
        //// 设置纹理选项
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 储存字符供之后使用
        Character characterResult = {
            texture,
            {face->glyph->bitmap.width, face->glyph->bitmap.rows},
            {face->glyph->bitmap_left, face->glyph->bitmap_top},
            face->glyph->advance.x,
            characterNum * fontSize,
        };
        Characters.insert(std::pair<char, Character>(character, characterResult));
        characterNum++;
        needAddTextures.push_back(character);
        return characterResult;
    }

    void FontSource::updateCharacterTexture()
    {
        FontManager::GetInstance()->updateCharacterTexture(this);

    }


    FontManager* FontManager::instance = nullptr;
    std::map<std::string, FontSource*> FontManager::sources = std::map<std::string, FontSource*>();

    FontManager::FontManager()
    {

        Render::CreateShader("fontScourceShader", "/asserts/shaders/fontSourceShader.vert", "/asserts/shaders/fontSourceShader.frag");

        glGenFramebuffers(1, &fbo);
    }

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

    void FontManager::updateCharacterTexture(FontSource* source)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_READ_FRAMEBUFFER, texture);

        glTexImage2D(GL_READ_FRAMEBUFFER, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_READ_FRAMEBUFFER, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_READ_FRAMEBUFFER, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_READ_FRAMEBUFFER, 0);

        // 将它附加到当前绑定的帧缓冲对象
        glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            printf("error");
        }


        float width = 1.0f * source->texturesCharacterNum * source->fontSize;
        float height = 1.0f * source->fontSize;

        RenderUIMesh* mesh = new RenderUIMesh("");

        std::vector<Core::AUIMesh::Vertex> vertices;
        std::vector<unsigned int> indices;

        Core::AUIMesh::Vertex vertex1;
        //vertex1.Position = Math::Vector3(-0.5f, -0.5f, 0);
        vertex1.Position = Math::Vector3(0.0f, 0.0f, 0);
        vertex1.TexCoords = Math::Vector2(0, 0);
        vertices.push_back(vertex1);

        Core::AUIMesh::Vertex vertex2;
        vertex2.Position = Math::Vector3(width, 0.0f, 0);
        vertex2.TexCoords = Math::Vector2(1, 0);
        vertices.push_back(vertex2);

        Core::AUIMesh::Vertex vertex3;
        vertex3.Position = Math::Vector3(0.0f, height, 0);
        vertex3.TexCoords = Math::Vector2(0, 1);
        vertices.push_back(vertex3);

        Core::AUIMesh::Vertex vertex4;
        vertex4.Position = Math::Vector3(width, height, 0);
        vertex4.TexCoords = Math::Vector2(1, 1);
        vertices.push_back(vertex4);

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(2);
        indices.push_back(1);
        indices.push_back(3);

        mesh->BindArrayBufferData(indices.size(), vertices.size() * sizeof(Core::AUIMesh::Vertex), &vertices[0]);
        mesh->BindElementBufferData(indices.size() * sizeof(unsigned int), &indices[0]);

        mesh->VertexAttribPointer(0, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(Core::AUIMesh::Vertex), offsetof(Core::AUIMesh::Vertex, Position));
        // vertex texture coords
        mesh->VertexAttribPointer(1, 2, Render::ShaderParamType::SPT_VEC2, false, sizeof(Core::AUIMesh::Vertex), offsetof(Core::AUIMesh::Vertex, TexCoords));
    
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, source->texture);
        GLShader* shader = GLShaderManager::Instance()->GetShaderObj("fontScourceShader");
        shader->setTexture("screenTexture", 0);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


        for (auto ch : source->needAddTextures)
        {

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
            GLubyte c = 0;

            // 加载字符的字形 
            if (FT_Load_Char(source->face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            }
            // 生成纹理
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                source->face->glyph->bitmap.width,
                source->face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                source->face->glyph->bitmap.buffer
            );
            // 设置纹理选项
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


            std::vector<Core::AUIMesh::Vertex> vertices;
            std::vector<unsigned int> indices;

            float endWidth = width + source->face->glyph->bitmap.width;

            Core::AUIMesh::Vertex vertex1;
            //vertex1.Position = Math::Vector3(-0.5f, -0.5f, 0);
            vertex1.Position = Math::Vector3(width, 0.0f, 0);
            vertex1.TexCoords = Math::Vector2(0, 0);
            vertices.push_back(vertex1);

            Core::AUIMesh::Vertex vertex2;
            vertex2.Position = Math::Vector3(endWidth, 0.0f, 0);
            vertex2.TexCoords = Math::Vector2(1, 0);
            vertices.push_back(vertex2);

            Core::AUIMesh::Vertex vertex3;
            vertex3.Position = Math::Vector3(width, height, 0);
            vertex3.TexCoords = Math::Vector2(0, 1);
            vertices.push_back(vertex3);

            Core::AUIMesh::Vertex vertex4;
            vertex4.Position = Math::Vector3(endWidth, height, 0);
            vertex4.TexCoords = Math::Vector2(1, 1);
            vertices.push_back(vertex4);

            indices.push_back(0);
            indices.push_back(1);
            indices.push_back(2);
            indices.push_back(2);
            indices.push_back(1);
            indices.push_back(3);

            mesh->BindArrayBufferData(indices.size(), vertices.size() * sizeof(Core::AUIMesh::Vertex), &vertices[0]);
            mesh->BindElementBufferData(indices.size() * sizeof(unsigned int), &indices[0]);

            mesh->VertexAttribPointer(0, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(Core::AUIMesh::Vertex), offsetof(Core::AUIMesh::Vertex, Position));
            // vertex texture coords
            mesh->VertexAttribPointer(1, 2, Render::ShaderParamType::SPT_VEC2, false, sizeof(Core::AUIMesh::Vertex), offsetof(Core::AUIMesh::Vertex, TexCoords));



            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, source->texture);
            GLShader* shader = GLShaderManager::Instance()->GetShaderObj("fontScourceShader");
            shader->setTexture("screenTexture", 0);

            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

            width += 1.0f * source->fontSize;
        }


        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
}
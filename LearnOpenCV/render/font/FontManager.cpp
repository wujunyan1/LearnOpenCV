#include "FontManager.h"
#include "../../file/FilePathManager.h"

#include "../render/RenderUIMesh.h"
#include "../meshModel/AUIMesh.h"

#include "../opengl/GLShader.h"
#include "../opengl/GLShaderManager.h"

#include "../render/RenderMain.h"
#include "../file/Image.h"

namespace Render
{
	FontSource::FontSource(std::string font)
	{
		fontName = font;

		if (FT_Init_FreeType(&ft))
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;


		std::string s = std::string(FilePathManager::getRootPath()) + font;
        printf("font path : %s \n", s.c_str());
		if (FT_New_Face(ft, s.c_str(), 0, &face))
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
        unsigned int texture;
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

        image = new Core::ImageFont(fontName, texture);
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

        // 储存字符供之后使用
        Character characterResult = {
            image->getTextureId(),
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


    void FontManager::checkCharacterTexture()
    {
        for (auto it : sources)
        {
            if (it.second->needAddTextures.size() > 0)
            {
                updateCharacterTexture(it.second);
            }
        }
    }

    void FontManager::updateCharacterTexture(FontSource* source)
    {
        GL_GET_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, fbo));

        unsigned int texture;
        GL_GET_ERROR(glGenTextures(1, &texture));
        GL_GET_ERROR(glBindTexture(GL_TEXTURE_2D, texture));

        GL_GET_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));

        GL_GET_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_GET_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GL_GET_ERROR(glBindTexture(GL_TEXTURE_2D, 0));

        // 将它附加到当前绑定的帧缓冲对象
        GL_GET_ERROR(glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0));

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            printf("error");
        }

        GLShader* shader = GLShaderManager::Instance()->GetShaderObj("fontScourceShader");
        shader->use();

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
    
        //float planeVertices[] = {
        //    // positions          // texture Coords 
        //     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
        //    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        //    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

        //     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
        //    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
        //     5.0f, -0.5f, -5.0f,  1.0f, 1.0f
        //};

        //unsigned int planeVAO, planeVBO;
        //glGenVertexArrays(1, &planeVAO);
        //glGenBuffers(1, &planeVBO);
        //glBindVertexArray(planeVAO);
        //glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
        //glEnableVertexAttribArray(0);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        //glEnableVertexAttribArray(1);
        //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        /*glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, source->texture);*/

        GL_GET_ERROR(glBindVertexArray(mesh->tvao));
        //GL_GET_ERROR(glBindVertexArray(planeVAO));

        GL_GET_ERROR(source->image->use(0));
        GL_GET_ERROR(shader->setTexture("screenTexture", 0));


        float left = 0.0f;
        float right = 1.0f * (source->characterNum * source->fontSize);
        float top = 1.0f * (source->fontSize);
        float bottom = 0.0f;
        float near = -1.0f;
        float far = 1.0f;

        Core::Mat4 ortho = Core::Mat4(1);
        ortho.m00 = (1.0f) / (right - left);
        ortho.m11 = (1.0f) / (top - bottom);
        ortho.m22 = -(2.0f) / (far - near);

        //glm::mat4 model = glm::ortho(0, (int)(source->characterNum * source->fontSize), 0, (int)source->fontSize);
        shader->setMat4("model", ortho);
        /*int modelLoc = glGetUniformLocation(shader->getID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)&model);*/

        GL_GET_ERROR(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices));


        for (auto ch : source->needAddTextures)
        {

            GL_GET_ERROR(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); //禁用字节对齐限制
            GLubyte c = 0;

            // 加载字符的字形 
            if (FT_Load_Char(source->face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            }
            // 生成纹理
            GLuint charTexture;
            GL_GET_ERROR(glGenTextures(1, &charTexture));
            GL_GET_ERROR(glBindTexture(GL_TEXTURE_2D, charTexture));
            GL_GET_ERROR(glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                source->face->glyph->bitmap.width,
                source->face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                source->face->glyph->bitmap.buffer
            ));
            // 设置纹理选项
            GL_GET_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
            GL_GET_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
            GL_GET_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            GL_GET_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


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



            GL_GET_ERROR(glActiveTexture(GL_TEXTURE0));
            GL_GET_ERROR(glBindTexture(GL_TEXTURE_2D, charTexture));
            GLShader* shader = GLShaderManager::Instance()->GetShaderObj("fontScourceShader");
            shader->use();
            shader->setTexture("screenTexture", 0);

            GL_GET_ERROR(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));

            width += 1.0f * source->fontSize;
        }

        delete source->image;

        source->image = new Core::ImageFont(source->fontName, texture);
        source->needAddTextures.clear();
        source->texturesCharacterNum = source->characterNum;

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
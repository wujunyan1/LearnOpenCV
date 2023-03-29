#pragma once

#include "../math/Math.h"
#include "../Core/Camera.h"
#include "../file/Image.h"

#include "../opengl/GLShader.h"

namespace Render
{
	class RenderSkyBox
	{
	public:
		RenderSkyBox();
		~RenderSkyBox();

		virtual void beforeRender() {};
		void render(Core::Camera* renderCamera);

        void UpdateSkyBoxImage(Core::ImageCubeMap* image) { m_image = image; };

	private:
        float skyboxVertices[108] = {
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
        };

        unsigned int skyboxIndices[36] = {
            2, 0, 4,
            4, 6, 2,

            1, 0, 2,
            2, 3, 1,

            4, 5, 7,
            7, 6, 4,

            1, 3, 7,
            7, 5, 1,

            2, 6, 7,
            7, 3, 2,

            0, 1, 4,
            4, 1, 5
        };

        GLShader* skyboxShader;
        Core::ImageCubeMap* m_image;

        unsigned int skyboxVAO;
        unsigned int skyboxVBO;
        unsigned int skyboxEBO;
	};
}
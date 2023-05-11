#pragma once
#include "Core.h"
#include "Component.h"
#include "Camera.h"
#include "../file/ImageLoad.h"
#include "../render/RenderSkyBox.h"

namespace Core
{
	class SkyBox : public GameComponent
	{
	public:
		SkyBox();

		void SetImags(std::vector<std::string>& faces);

		void Bind();

		void OnDestroy();

		Render::RenderSkyBox* getRenderSkyBox() { return render_skyBox; };

	private:

		ImageCubeMap* image;
		Render::RenderSkyBox* render_skyBox;
	};
}

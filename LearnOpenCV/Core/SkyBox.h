#pragma once
#include "Core.h"
#include "Component.h"
#include "Camera.h"
#include "../file/ImageLoad.h"

namespace Core
{
	class SkyBox : public Component
	{
	public:
		SkyBox();

		void Bind();


	private:

		ImageCubeMap* image;
	};
}

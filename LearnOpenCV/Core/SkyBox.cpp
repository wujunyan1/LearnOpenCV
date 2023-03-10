#include "SkyBox.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "Camera.h"
#include "Model.h"

#include "../math/Math.h"
#include "../render/RenderSkyBox.h"

using namespace Core;

SkyBox::SkyBox()
{
	image = nullptr;
	render_skyBox = new Render::RenderSkyBox();
}

void Core::SkyBox::SetImags(std::vector<std::string>& faces)
{
	if (image)
	{
		ImageLoad::DestroyImage(image);
		image = nullptr;
	}
	image = ImageLoad::CreateImageCubeMap(faces[0], faces);

	render_skyBox->UpdateSkyBoxImage(image);
}

void SkyBox::Bind()
{
}

void Core::SkyBox::OnDestroy()
{
	if (image)
	{
		ImageLoad::DestroyImage(image);
		image = nullptr;
	}

	delete render_skyBox;
	render_skyBox = nullptr;
}

#pragma once
#include "../Core/Core.h"
#include "../Core/Component.h"
#include "../Core/Object.h"
#include "../file/Image.h"
#include "../file/ImageLoad.h"
#include "../render/RenderMain.h"
#include "../meshModel/AUIMesh.h"
#include "../Core/RenderInterface.h"
#include <vector>

using namespace Core;
namespace UI 
{
	class UIImage : public GameComponent, public RenderInterface
	{
	public:

		UIImage();

		void setImage(std::string& name);

		// 目标是深度缓存里的， src是ps输出的
		void setBlendFunc(Render::BlendFunc src, Render::BlendFunc target);

		void setColor(Vector3 color) { m_color = color; };

		virtual void Render();

	private:
		void initModel();

	private:
		std::string imageName = "";
		Image* image = nullptr;

		Vector3 m_color = { 1,1,1 };
		Render::BlendFunc srcBlendFunc = Render::BlendFunc::SRC_ALPHA;
		Render::BlendFunc targetBlendFunc = Render::BlendFunc::ONE_MINUS_SRC_ALPHA;

		// 材质
		Render::RenderProgram* renderProgram = NULL;

		AModel* model = NULL;
		Render::Texture texture;
	};
}

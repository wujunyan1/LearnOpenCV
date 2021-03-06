#pragma once
#include "Core.h"
#include "Component.h"
#include "../math/Math.h"
#include "../render/RenderMain.h"
#include "../meshModel/AModel.h"
#include "../render/BlendFunc.h"

namespace Core
{
	class Model : public Component
	{
	public:
		Model();

		void setModel(AModel* model);
		

		void bindRender();

		void Render();

		void setShader(std::string shaderName);

		// 是否开启深度测试，默认开启
		void setBlend(bool enable);

		// 目标是深度缓存里的， src是ps输出的
		void setBlendFunc(Render::BlendFunc src, Render::BlendFunc target);

		// 是否开启深度测试，默认开启
		void setDepthTest(bool enable);
	private:
		// 材质
		Render::RenderProgram* renderProgram = NULL;
	};
}

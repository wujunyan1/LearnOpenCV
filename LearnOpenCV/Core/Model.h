#pragma once
#include "Core.h"
#include "Component.h"
#include "../math/Math.h"
#include "../render/RenderMain.h"
#include "../meshModel/AModel.h"
#include "../render/BlendFunc.h"
#include "RenderInterface.h"

namespace Core
{
	class Model : public GameComponent, public RenderInterface
	{
	public:
		Model();
		~Model();

		void setModel(AModel* model);
		

		void bindRender();

		virtual void Render();

		void setShader(std::string shaderName);

		void setRenderQueue(std::string renderName);

		void setRenderStageIndex(unsigned int stage);

		// 是否开启混合模式
		void setBlend(bool enable);

		// 目标是深度缓存里的， src是ps输出的
		void setBlendFunc(Render::BlendFunc src, Render::BlendFunc target);

		// 是否开启深度测试，默认开启
		void setDepthTest(bool enable);
	private:
		// 材质
		Render::RenderProgram* renderProgram = NULL;

		bool b_isShow = true;

		float f_alpha = 1.0f;

	private:
	};
}

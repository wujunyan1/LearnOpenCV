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

		// �Ƿ�����Ȳ��ԣ�Ĭ�Ͽ���
		void setBlend(bool enable);

		// Ŀ������Ȼ�����ģ� src��ps�����
		void setBlendFunc(Render::BlendFunc src, Render::BlendFunc target);

		// �Ƿ�����Ȳ��ԣ�Ĭ�Ͽ���
		void setDepthTest(bool enable);
	private:
		// ����
		Render::RenderProgram* renderProgram = NULL;
	};
}
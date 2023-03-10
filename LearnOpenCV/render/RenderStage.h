#pragma once

#include "../math/Math.h"

#include "../Core/Camera.h"

#include "../render/RenderQueue.h"

namespace Render
{
	class RenderStage
	{
		friend class RenderStageManager;
	public:
		RenderStage(unsigned int index);

		~RenderStage();


		void AddRenderProgram(RenderProgram* renderProgram);

		void beforeRender();
		virtual void render(Core::Camera* renderCamera);
		void renderEnd();

		unsigned int getRenderStage() { return renderStage; };
	private:
		Render::RenderQueue* createRenderQueue(const std::string& type);

	private:
		unsigned int renderStage = 0;
		std::map<unsigned int, Render::RenderQueue*>* queues;
	};

	class SkyBoxRenderStage : public RenderStage
	{
	public:
		SkyBoxRenderStage(unsigned int index) : RenderStage(index) {};

		void render(Core::Camera* renderCamera);
	};

	class RenderStageManager
	{
		static const unsigned int RENDER_SKY_BOX_STAGE = 19999;

	public:
		static void beforeRender();
		static void render(Core::Camera* renderCamera);
		static void renderEnd();

		static void AddRenderProgram(RenderProgram* renderProgram);
	private:
		static std::map<unsigned int, RenderStage*> stages;
		static std::vector<RenderStage*> renderStages;
	};
}
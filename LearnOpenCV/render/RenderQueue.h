#pragma once

#include "../Core/Core.h"
#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "RenderMesh.h"
#include "BlendFunc.h"

#include "../Core/Camera.h"
#include "../meshModel/AModel.h"

namespace Render
{
	class RenderProgram
	{
		friend class RenderQueue;
	public:
		RenderProgram();

		virtual RenderMesh* createNewRenderMesh(std::string name = Math::stringFormat("renderMesh|%d", Math::getUid()));
		virtual RenderMesh* loadRenderMesh(std::string name, std::string path = "");

		void setModel(Core::AModel* model) 
		{
			_model = model;
		};

		ShaderProgram* getShaderProgram() { return shaderProgram; }
		Material* getMaterial() { return material; }

		void setMaterialName(const std::string name) { materialName = name; };
		std::string& getMaterialName() { return materialName; };

		virtual void setShader(const std::string& shaderName);

		virtual void Render();

		void setRenderQueueName(const std::string renderQueueName) { renderQueue = renderQueueName; };
		std::string& getRenderQueueName() { return renderQueue; };

		// 目标是深度缓存里的， src是ps输出的
		void setBlendFunc(Render::BlendFunc src, Render::BlendFunc target) {
			this->srcBlendFunc = src;
			this->targetBlendFunc = target;
		};

		// 目标是深度缓存里的， src是ps输出的
		void setBlend(bool blend) {
			this->blend = blend;
		};

		// 是否开启深度测试，默认开启
		void setDepthTest(bool enable) { depthTest = enable; };

		std::string getQueueName() { return this->queueName; };
		void setQueue(std::string name) { this->queueName = name; };

		void setRenderStage(unsigned int stage) { this->renderStage = stage; };
		unsigned int getRenderStage() { return this->renderStage; };

		void setLocalToWorldMat4(Math::Matrix4& lTw) 
		{
			if (_model == nullptr)
			{
				return;
			}

			renderAABB.initVertices(_model->getObb().getPoints());
			renderAABB.localToWorld(lTw);
		};

		Math::AABB& getRenderAABB() { return renderAABB; };

	protected:
		ShaderProgram* shaderProgram;

		std::string materialName;
		Material* material;

		Core::AModel* _model = nullptr;

		std::string renderQueue;

		unsigned int renderStage = 0;

		bool depthTest = true;

		// 是否启用混合模式
		bool blend = false;
		BlendFunc srcBlendFunc = BlendFunc::SRC_ALPHA;
		BlendFunc targetBlendFunc = BlendFunc::ONE_MINUS_SRC_ALPHA;

		std::string queueName;

		Math::AABB renderAABB;

		Core::ui64 renderLayer = 1;
	public:
		float cameraDistance = 999999.9f;
	};

	class RenderQueue
	{
	public:
		RenderQueue();
		~RenderQueue();

		virtual void Render(Core::Camera* camera);

		void addRenderProgram(RenderProgram* renderProgram);

		virtual void clear();

	protected:

		unsigned int renderSort;

		unsigned int index;

		// 这个队列的shader
		ShaderProgram* shaderProgram;

		// 激活的需要渲染的
		std::vector<RenderProgram*>* activeRenderProgram;
	};


	class RenderQueueManager
	{
	public:
		// for create instance Instance
		typedef std::function<Render::RenderQueue* ()> RenderCreator;
		typedef std::map<std::string, RenderCreator> RenderQueueCreatorMap;

		static void registerRenderQueueCreator(const std::string& type, RenderCreator creator);
		static Render::RenderQueue* createRenderQueue(const std::string& type);

		static void AddRenderQueue(RenderProgram* renderProgram);

		static void RenderQueue();
		static void ClearRenderQueue();

	public:
		static RenderQueueManager::RenderQueueCreatorMap& GetRenderQueueCreatorMap()
		{
			static RenderQueueCreatorMap map;
			return map;
		}

	private:
		static std::map<unsigned int, Render::RenderQueue*>* queues;
	};
}
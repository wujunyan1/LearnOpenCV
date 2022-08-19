#pragma once

#include "../Core/Core.h"
#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "RenderMesh.h"
#include "BlendFunc.h"

#include "../meshModel/AModel.h"

namespace Render
{
	class RenderProgram
	{
	public:
		RenderProgram();

		virtual RenderMesh* createNewRenderMesh(std::string name = Math::stringFormat("renderMesh|%d", Math::getUid())) { return NULL; };
		virtual RenderMesh* loadRenderMesh(std::string name, std::string path = "") { return NULL; };

		std::vector <RenderMesh*>* getMeshs() { return meshs; }
		void addMesh(RenderMesh* mesh) { 
			if (!meshs) {
				meshs = new std::vector<RenderMesh*>();
			}
			meshs->push_back(mesh); 
		}
		virtual void addModel(Core::AModel* model) {};

		ShaderProgram* getShaderProgram() { return shaderProgram; }
		Material* getMaterial() { return material; }

		virtual void setShader(const std::string& shaderName) {};

		virtual void Render() {};

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
	protected:
		ShaderProgram* shaderProgram;

		Material* material;

		std::vector<RenderMesh*>* meshs;

		std::string renderQueue;

		bool depthTest = true;

		// 是否启用混合模式
		bool blend = false;
		BlendFunc srcBlendFunc = BlendFunc::SRC_ALPHA;
		BlendFunc targetBlendFunc = BlendFunc::ONE_MINUS_SRC_ALPHA;

		std::string queueName;
	};

	class RenderQueue
	{
	public:
		RenderQueue();
		~RenderQueue();

		void Render();

		void addRenderProgram(RenderProgram* renderProgram);

		void clear();

	protected:

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

	private:
		static RenderQueueManager::RenderQueueCreatorMap& GetRenderQueueCreatorMap()
		{
			static RenderQueueCreatorMap map;
			return map;
		}

		static std::map<unsigned int, Render::RenderQueue*>* queues;
	};
}
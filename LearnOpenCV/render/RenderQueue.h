#pragma once

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

		// Ŀ������Ȼ�����ģ� src��ps�����
		void setBlendFunc(Render::BlendFunc src, Render::BlendFunc target) {
			this->srcBlendFunc = src;
			this->targetBlendFunc = target;
		};

		// Ŀ������Ȼ�����ģ� src��ps�����
		void setBlend(bool blend) {
			this->blend = blend;
		};

		// �Ƿ�����Ȳ��ԣ�Ĭ�Ͽ���
		void setDepthTest(bool enable) { depthTest = enable; };

		void setQueue(std::string name) { this->queueName = name; };
	protected:
		ShaderProgram* shaderProgram;

		Material* material;

		std::vector<RenderMesh*>* meshs;

		bool depthTest = true;

		// �Ƿ����û��ģʽ
		bool blend = false;
		BlendFunc srcBlendFunc = BlendFunc::SRC_ALPHA;
		BlendFunc targetBlendFunc = BlendFunc::ONE_MINUS_SRC_ALPHA;

		std::string queueName;
	};

	class RenderQueue
	{
	public:
		RenderQueue(ShaderProgram* program);
		~RenderQueue();

		void Render();

		void addRenderProgram(RenderProgram* renderProgram);

		void clear();

	private:

		unsigned int index;

		// ������е�shader
		ShaderProgram* shaderProgram;

		// �������Ҫ��Ⱦ��
		std::vector<RenderProgram*>* activeRenderProgram;
	};


	class RenderQueueManager
	{
	public:
		static void AddRenderQueue(RenderProgram* renderProgram);

		static void RenderQueue();

		static void AddCustomRenderQuene();

	private:


	private:
		static std::map<unsigned int, Render::RenderQueue*>* queues;
	};
}
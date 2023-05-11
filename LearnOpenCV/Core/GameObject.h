#pragma once

#include <vector>
#include "Component.h"
#include "Core.h"
#include "TreeNode.h"
#include "RenderInterface.h"

namespace Core {
	class GameObject : public TreeNode
	{
	public:
		friend class ObjectManager;

	public:
		GameObject() : TreeNode()
		{
		}

		~GameObject() {
		}

		virtual void PreUpdate() {
			for (auto i : *componentList)
			{
				if (i->isActive())
					i->PreUpdate();
			}

			TreeNode::PreUpdate();
		}
		virtual void Update() {
			for (auto i : *componentList)
			{
				if (i->isActive())
					i->Update();
			}

			TreeNode::Update();
		}
		virtual void LaterUpdate() {
			for (auto i : *componentList)
			{
				if (i->isActive())
					i->LaterUpdate();
			}

			TreeNode::LaterUpdate();
		}

		virtual void Render() {
			for (auto i : *componentList)
			{
				if (i->isActive())
				{
					RenderInterface* renderModel = dynamic_cast<RenderInterface*>(i);
					if (renderModel)
					{
						renderModel->Render();
					}
				}
			}

			TreeNode::Render();
		}

	};


}
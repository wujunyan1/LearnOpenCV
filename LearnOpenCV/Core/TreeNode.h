#pragma once
#include "Core.h"
#include "Ref.h"
#include <vector>

namespace Core 
{
	class TreeNode : public Ref
	{
	public:

		TreeNode() {
			children = NULL;
			parent = NULL;
		}

		TreeNode* GetParent()
		{
			return parent;
		}

		TreeNode* GetRoot()
		{
			TreeNode* node = parent;
			TreeNode* beforeNode = parent;
			while (node)
			{
				beforeNode = node;
				node = node->GetParent();
			}

			return beforeNode;
		}

		void AddChild(TreeNode* child) {
			if (children == NULL) {
				children = new std::vector<TreeNode*>();
			}
			if (child->parent) {
				child->parent->removeChild(child);
			}

			child->parent = this;
			child->retain();
			children->push_back(child);
		}

		void removeChild(TreeNode* child) {
			if (children == NULL) {
				return;
			}
			
			if (child->parent != this)
			{
				return;
			}

			std::vector<TreeNode*>::iterator itor = children->begin();
			while (itor != children->end())
			{
				TreeNode* c = *itor;
				if (child == c) {
					itor = children->erase(itor);
					break;
				}
			}
			child->parent = nullptr;
			child->release();
		}

		TreeNode* GetChildByIndex(int index) {
			return children->at(index);
		}

		std::vector<TreeNode*>* getChildren() {
			return children;
		}

		virtual void PreUpdate() {
			if (children == nullptr) {
				return;
			}
			for (auto i : *children)
			{
				i->PreUpdate();
			}
		}
		virtual void Update() {
			if (children == nullptr) {
				return;
			}
			for (auto i : *children)
			{
				i->Update();
			}
		}
		virtual void LaterUpdate() {
			if (children == nullptr) {
				return;
			}
			for (auto i : *children)
			{
				i->LaterUpdate();
			}
		}

		virtual void Render() {
			if (children == nullptr) {
				return;
			}
			for (auto i : *children)
			{
				i->Render();
			}
		}

	protected:
		std::vector<TreeNode*>* children;
		TreeNode* parent;
	};


}

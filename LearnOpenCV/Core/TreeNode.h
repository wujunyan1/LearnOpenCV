#pragma once
#include "Core.h"
#include "Ref.h"
#include "Object.h"
#include <vector>

namespace Core 
{
	class TreeNode : public Object
	{
	public:

		TreeNode() {
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
			if (child->parent) {
				child->parent->removeChild(child);
			}

			child->parent = this;
			child->retain();
			children.push_back(child);

			childOrderChange = true;
		}

		void removeChild(TreeNode* child) {
			if (child->parent != this)
			{
				return;
			}

			std::vector<TreeNode*>::iterator itor = children.begin();
			while (itor != children.end())
			{
				TreeNode* c = *itor;
				if (child == c) {
					itor = children.erase(itor);
					break;
				}
			}
			child->parent = nullptr;
			child->release();
		}

		TreeNode* GetChildByIndex(int index) {
			return children.at(index);
		}

		std::vector<TreeNode*>& getChildren() {
			return children;
		}

		unsigned int getOrder() { return m_order; };
		void setOrder(unsigned int order) 
		{ 
			m_order = order; 
			_orderOfArrival = ++global_orderOfArrival;
			if (parent)
			{
				parent->childOrderChange = true;
			}
		};


		virtual void PreUpdate() {
			for (auto i : children)
			{
				i->PreUpdate();
			}
		}
		virtual void Update() {
			for (auto i : children)
			{
				i->Update();
			}
		}
		virtual void LaterUpdate() {
			for (auto i : children)
			{
				i->LaterUpdate();
			}
		}

		virtual void Render() {
			if (childOrderChange)
			{
				sortNodes();
				childOrderChange = false;
			}
			for (auto i : children)
			{
				i->Render();
			}
		}

	private:
		void sortNodes()
		{
			std::sort(std::begin(children), std::end(children), [](TreeNode* n1, TreeNode* n2) {
				return (n1->m_order == n2->m_order && n1->_orderOfArrival < n2->_orderOfArrival) || n1->m_order < n2->m_order;
				});
		}

		void childrenChangeOrder()
		{

		}

	protected:
		std::vector<TreeNode*> children;
		TreeNode* parent;
		unsigned int m_order = 50;
		unsigned int _orderOfArrival = 0;
		std::string name;
		bool childOrderChange = false;

		static unsigned int global_orderOfArrival;
	};


}

#include "GameObject.h"
#include "../opengl/OpenGLCore.h"

using namespace Core;

void Core::GameObject::Update()
{
	{
		for (auto i : *componentList)
		{
			if (i->isActive())
			{
				i->Update();
				/*printf("%s \n", typeid(*i).name());
				GL_GET_ERROR();*/
			}
		}

		TreeNode::Update();
	}
}

#pragma once
#include <iostream>

namespace Core
{
	class Image
	{

	public:
		virtual void use(int textureIndex) {};
		virtual void exit(int textureIndex) {};
	};

}
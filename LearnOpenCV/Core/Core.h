#pragma once

// C 运行时头文件
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <map>

#include "TypeDef.h"

#include "../math/Math.h"

namespace Core 
{
	typedef Math::Vector1			Vector1;
	typedef Math::Vector2			Vector2;
	typedef Math::Vector3			Vector3;
	typedef Math::Vector4			Vector4;
	typedef Math::Matrix4			Mat4;

	typedef std::string			String;

}


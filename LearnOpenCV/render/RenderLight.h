#pragma once

#include "../math/Math.h"

#include "../Core/Camera.h"

using namespace Math;

namespace Render
{
	enum LightType
	{
		DIR,
		POINT,
	};

	struct RenderLight
	{
		bool b_active = false;
		LightType type = LightType::DIR;

		Vector3 m_position;
		Vector3 m_dir;

		// color
		Vector3 m_diffuse;
	};

	class RenderLightManager
	{
	private:
		static std::vector<RenderLight> m_dirLights;
		static std::vector<RenderLight> m_pointLights;
	};
}
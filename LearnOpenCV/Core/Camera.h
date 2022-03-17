#pragma once
#include "Core.h"
#include "Component.h"

namespace Core
{
	class Transform;

	class Camera : public Component
	{
	public:
		Camera();

		void Bind();
		void init(float fov, float aspect, float near, float far);

		Mat4& getViewMat4();
		Mat4& getPerspectiveMat4();
		Mat4& getOrthogonalMat4();
		Mat4& getVPMat4();

		virtual void LaterUpdate() override;

	private:
		Transform* transform;

		float eye_fov, aspect_ratio, near, far;

		Math::Matrix4 orthogonal;
		Math::Matrix4 perspective;
		Math::Matrix4 vp;

	};
}

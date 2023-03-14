#pragma once
#include "Core.h"
#include "Component.h"

namespace Core
{
	class Transform;
	class Scene;
	class EventListenerCustom;

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

		void SetMainCamera(bool isMain);
		bool GetMainCamera() { return m_isMainCamera; };
		void Render();

		Math::AABB& getPerspectiveAABB() { return perspectiveAabb; };
		Math::Vector3& getWorldPosition() { return worldPosition; };

		void beginRender();

	private:
		Transform* transform;

		float eye_fov, aspect_ratio, near, far;

		Math::Matrix4 orthogonal;
		Math::Matrix4 perspective;
		Math::Matrix4 vp;

		float n_top, n_bottom, n_left, n_right;
		float f_top, f_bottom, f_left, f_right;

		Math::AABB perspectiveAabb;
		Math::Vector3 worldPosition;

		bool m_isMainCamera = false;

	private:
		unsigned int fbo = 0;

		EventListenerCustom* winSizeChangeEventListener;
	};
}

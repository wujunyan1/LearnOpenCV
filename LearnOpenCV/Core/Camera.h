#pragma once
#include "Core.h"
#include "Component.h"
#include "RenderInterface.h"

namespace Core
{
	class Transform;
	class Scene;
	class EventListenerCustom;

	class Camera : public GameComponent, public RenderInterface
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
		virtual void Render();

		Math::AABB& getPerspectiveAABB() { return perspectiveAabb; };
		Math::Vector3& getWorldPosition() { return worldPosition; };

		ui64 getCullingMask() { return m_cullingMask; }
		void setCullingMask(ui64 mask) { m_cullingMask = mask; }

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

		ui64 m_cullingMask = std::numeric_limits<ui64>::max();

	private:
		unsigned int fbo = 0;

		EventListenerCustom* winSizeChangeEventListener;
	};
}

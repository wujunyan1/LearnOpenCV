#include "Camera.h"
#include "Transform.h"
#include "Scene.h"
#include "../render/RenderMain.h"
#include "Game.h"
#include "../event/EventDispatcher.h"
#include "../event/EventListenerCustom.h"
#include "../math/Vector2T.h"
#include "GlobalDictionary.h"

using namespace Core;

Camera::Camera()
{
	printf("Camera");
	//transform = getObject()->GetComponent<Transform>();
	
	winSizeChangeEventListener = GlobalDictionary::getDispatcher()->addCustomEventListener("winSizeChangeEvent", [this](EventCustom* _event) {
		Math::Vector2T<int>* size = (Math::Vector2T<int>*)_event->getUserData();
		this->init(eye_fov, size->x * 1.0f / size->y, near, far);
	});
}

void Camera::Bind()
{
	transform = getObject()->GetComponent<Transform>();
}

void Camera::init(float fov, float aspect, float near, float far)
{
	this->eye_fov = fov;
	this->aspect_ratio = aspect;
	this->near = near;
	this->far = far;


	float top = std::tan(eye_fov / 2.0f) * near;
	float right = aspect_ratio * top;
	float bottom = -top;
	float left = -right;

	this->n_top = top;
	this->n_right = right;
	this->n_bottom = bottom;
	this->n_left = left;

	this->f_top = std::tan(eye_fov / 2.0f) * far;
	this->f_right = aspect_ratio * this->f_top;
	this->f_bottom = -this->f_top;
	this->f_left = -this->f_right;


	float tanHalfFovy = tan(eye_fov / 2.0f);
	perspective = Mat4(
		1.0f / (aspect * tanHalfFovy), 0, 0, 0,
		0, 1.0f / (tanHalfFovy), 0, 0,
		0, 0, -(near + far) / (far - near), -2.0f * near * far / (far - near),
		0, 0, -1.0f, 0
	);
}

Mat4& Camera::getViewMat4()
{
	return transform->GetWorldToLocalMat4();
}

Mat4& Camera::getPerspectiveMat4()
{
	return perspective;
}

Mat4& Camera::getOrthogonalMat4()
{
	return orthogonal;
}

Mat4& Camera::getVPMat4()
{
	return vp;
}

void Camera::LaterUpdate()
{
	vp = perspective * getViewMat4();
}

void Core::Camera::SetMainCamera(bool isMain)
{
	m_isMainCamera = isMain;

	Scene* scene = dynamic_cast<Scene*>(getGameObject()->GetRoot());
	if (!scene)
	{
		return;
	}
	if (isMain)
	{
		scene->setMainCamera(this);
	}
}

void Core::Camera::Render()
{
	if (!b_isActive)
	{
		return;
	}

	Scene* scene = dynamic_cast<Scene*>(getGameObject()->GetRoot());
	if (!scene)
	{
		return;
	}
	if (!m_isMainCamera)
	{
		printf("camera no mainCamera \n");
		scene->addRenderCamera(this);
	}

	Math::Matrix4& m4 = transform->GetLocalToWorldMat4();

	Vector3 center = m4 * Vector4(0, 0, 0, 1);
	Vector3 xdir = m4 * Vector4(1, 0, 0, 0);
	Vector3 ydir = m4 * Vector4(0, 1, 0, 0);
	Vector3 zdir = m4 * Vector4(0, 0, 1, 0);

	xdir.normalize();
	ydir.normalize();
	zdir.normalize();

	Vector3 near = center - zdir * this->near;
	Vector3 far = center - zdir * this->far;

	Vector3 nright = xdir * this->n_right;
	Vector3 ntop = ydir * this->n_top;
	Vector3 fright = xdir * this->f_right;
	Vector3 ftop = ydir * this->f_top;

	std::vector<Vector3> points = {
		near + nright + ntop,
		near - nright + ntop,
		near + nright - ntop,
		near - nright - ntop,
		far + fright + ftop,
		far - fright + ftop,
		far + fright - ftop,
		far - fright - ftop
	};

	worldPosition = center;
	perspectiveAabb.initVertices(points);


}

void Core::Camera::beginRender()
{
	Render::BindFramebuffer(fbo);
}

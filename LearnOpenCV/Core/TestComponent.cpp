#include "TestComponent.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "Camera.h"

#include "../math/Math.h"

using namespace Core;
TestComponent::TestComponent()
{
}

void TestComponent::Bind()
{
}

void TestComponent::Update()
{
	Transform* transform = this->getObject()->GetComponent<Transform>();

	transform->SetPosition(transform->GetPosition() + Vector3(0.0f, 0.00f, -0.01f));
	//transform->SetRotate(transform->GetRotate() + Vector3(0.00f, 0.01f, 0.0f));
}
#include "CameraMoveComponent.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "Camera.h"
#include "Game.h"
#include "../input/Input.h"

#include "../math/Math.h"

using namespace Core;
CameraMoveComponent::CameraMoveComponent()
{
}

void CameraMoveComponent::Bind()
{
}

void CameraMoveComponent::Update()
{
    float delay = Game::GetInstance()->GetCurrUpdateDelay();

    Transform* transform = getObject()->GetComponent<Transform>();
    Vector3 cameraPos = transform->GetPosition();
    Vector3 cameraFront = transform->getForword();
    Vector3 cameraRight = transform->getRight();



    // 摄像机控制
    float cameraSpeed = delay * moveSpeed;
    if (Core::Input::isKeyDown(Input::Key::W)) {
        cameraPos -= cameraFront * cameraSpeed;
    }
    if (Core::Input::isKeyDown(Input::Key::S)) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (Core::Input::isKeyDown(Input::Key::A)) {
        cameraPos -= cameraRight * cameraSpeed;
    }
    if (Core::Input::isKeyDown(Input::Key::D)) {
        cameraPos += cameraRight * cameraSpeed;
    }

    transform->SetPosition(cameraPos);


    if (Core::Input::isMouseLeftDown(Input::Key::MOUSE_BUTTON_LEFT)) {
        if (!isTouchDown) {
            isTouchDown = true;
            preMousePos = Input::GetCurrMousePos();
        }
        Vector2 currMousePos = Input::GetCurrMousePos();

        float xoffset = currMousePos.x - preMousePos.x;
        float yoffset = currMousePos.y - preMousePos.y; // 注意这里是相反的，因为y坐标的范围是从下往上的
        preMousePos = currMousePos;

        float sensitivity = 0.01f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        //transform->SetRotate(rotate);
        transform->Rotate(Vector3(yoffset, xoffset, 0), Space::Self);
    }
    if (Core::Input::isMouseLeftUp(Input::Key::MOUSE_BUTTON_LEFT)) {
        isTouchDown = false;
    }

}
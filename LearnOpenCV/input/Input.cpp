#include "Input.h"

using namespace Core;

bool Input::keys[1024] = { false };
Math::Vector2 Input::mousePos = Math::Vector2();

void Input::PressKey(Key key)
{
	keys[(int)key] = true;
	printf("key: %d down\n", key);
}

void Input::ReleaseKey(Key key)
{
	keys[(int)key] = false;
	printf("key: %d up\n", key);
}

void Input::UpdateMousePosition(Math::Vector2 pos)
{
	mousePos = pos;
}

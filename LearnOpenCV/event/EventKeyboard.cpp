#include "EventKeyboard.h"

using namespace Core;

EventKeyboard::EventKeyboard(KeyCode keyCode, bool isPressed)
: Event(Type::KEYBOARD)
, _keyCode(keyCode)
, _isPressed(isPressed)
{}

#include "Event.h"
#include "../Core/TreeNode.h"

using namespace Core;

Event::Event(Type type)
: _type(type)
, _isStopped(false)
, _currentTarget(nullptr)
{
}

Event::~Event()
{
}

#include "scene/node.h"

#include "core/component_manager.h"

Node::Node() { id = ComponentManager::GetInstance()->newEntity(); }
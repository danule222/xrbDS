#include "scene/3d/node_3d.h"

#include "core/component_manager.h"
#include "components/transform.h"

Node3D::Node3D() {
  Transform transform{FVector3(0.f, 0.f, 0.f), FVector3(0.f, 0.f, 0.f),
                      FVector3(0.f, 0.f, 0.f)};
  ComponentManager::GetInstance()->addComponent(id, transform);
}
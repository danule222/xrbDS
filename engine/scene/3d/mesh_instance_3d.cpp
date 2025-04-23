#include "scene/3d/mesh_instance_3d.h"

#include "components/mesh_filter.h"

MeshInstance3D::MeshInstance3D(const FString &path) {
  ComponentManager::GetInstance()->addComponent<MeshFilter>(
      id, *MeshFilter::Initialize(path));
}
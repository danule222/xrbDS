#ifndef XRBDS_SCENE_3D_MESH_INSTANCE_H
#define XRBDS_SCENE_3D_MESH_INSTANCE_H

#include "scene/3d/node_3d.h"
#include "resources/mesh.h"

class MeshInstance3D : public Node3D {
public:
  using Super = Node3D;

public:
  MeshInstance3D();
};

#endif // XRBDS_SCENE_3D_MESH_INSTANCE_H
#ifndef XRBDS_SCENE_3D_MESH_INSTANCE_H
#define XRBDS_SCENE_3D_MESH_INSTANCE_H

#include "scene/3d/node_3d.h"
#include "resources/mesh.h"

class MeshInstance3D : public Node3D {
public:
  MeshInstance3D();
  virtual ~MeshInstance3D();

  // Add methods to set/get mesh, materials, etc.
  void set_mesh(const PtrShr<Mesh> &mesh);
  PtrShr<Mesh> get_mesh() const;

private:
  PtrShr<Mesh> mesh_;
};

#endif // XRBDS_SCENE_3D_MESH_INSTANCE_H
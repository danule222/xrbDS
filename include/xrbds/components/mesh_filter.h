#ifndef MESH_FILTER_H
#define MESH_FILTER_H

#include "component.h"
#include "core/types.h"

class Mesh;

struct MeshFilter : public Component {
public:
  static PtrUnq<MeshFilter> Initialize(const FString &path);

  PtrShr<Mesh> getMesh() const { return mesh; }

private:
  PtrShr<Mesh> mesh;

  MeshFilter(const FString &path);
};

#endif // MESH_FILTER_H
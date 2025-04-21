#ifndef MESH_FILTER_H
#define MESH_FILTER_H

#include "component.h"
#include "core/types.h"

class Mesh;

struct MeshFilter : public Component {
public:
  MeshFilter(const FString &name);

private:
  FString meshName;
  PtrShr<Mesh> mesh;
};

#endif // MESH_FILTER_H
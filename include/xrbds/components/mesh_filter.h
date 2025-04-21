#ifndef MESH_FILTER_H
#define MESH_FILTER_H

#include "core/types.h"

struct MeshFilter {
  FString meshName;

  MeshFilter(const FString &name) : meshName(name) {}
};

#endif // MESH_FILTER_H
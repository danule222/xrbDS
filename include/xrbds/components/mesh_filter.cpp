#include "mesh_filter.h"

#include "resources/resource.h"

MeshFilter::MeshFilter(const FString &name) : meshName(name) {
  mesh = LoadResource<Mesh>(name);
}
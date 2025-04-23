#include "components/mesh_filter.h"

#include "resources/resource.h"
#include "utils/file.h"

MeshFilter::MeshFilter(const FString &path) {
  // Load the mesh from the file
  auto vertices = Utils::File::ReadObjFile(path);

  mesh = LoadResource<Mesh>(vertices);
}

PtrUnq<MeshFilter> MeshFilter::Initialize(const FString &path) {
  return PtrUnq<MeshFilter>(new MeshFilter(path));
}
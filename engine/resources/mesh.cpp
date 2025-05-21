#include "resources/mesh.h"

Mesh Mesh::Load(const TVector<FShape> &shapes,
                const TVector<FMaterial> &materials,
                const TVector<PtrShr<Texture>> &textures) {
  return std::move(Mesh(shapes, materials, textures));
}

Mesh::Mesh(const TVector<FShape> &shapes, const TVector<FMaterial> &materials,
           const TVector<PtrShr<Texture>> &textures)
    : Super(), shapes(shapes), materials(materials), textures(textures) {}
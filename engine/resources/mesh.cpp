#include "resources/mesh.h"

Mesh Mesh::Load(const TVector<TVector<FVertex>> &vertices) {
  return std::move(Mesh(vertices));
}

Mesh::Mesh(const TVector<TVector<FVertex>> &vertices)
    : Super(), vertices(vertices) {}
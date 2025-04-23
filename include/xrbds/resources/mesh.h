#ifndef XRBDS_RESOURCES_MESH_H
#define XRBDS_RESOURCES_MESH_H

#include "resource.h"
#include "core/types.h"

#include <vector>

struct FVertex {
  FVector3 position;
  FVector3 normal;
  FVector2 texCoords;

  FVertex(const FVector3 &pos, const FVector3 &norm, const FVector2 &tex)
      : position(pos), normal(norm), texCoords(tex) {}
};

class Mesh : public Resource {
  using Super = Resource;

public:
  static Mesh Load(const TVector<TVector<FVertex>> &vertices);

  TVector<TVector<FVertex>> getVertices() const { return vertices; }

private:
  TVector<TVector<FVertex>> vertices;

  Mesh() = default;
  Mesh(const TVector<TVector<FVertex>> &vertices);
};

#endif // XRBDS_RESOURCES_MESH_H
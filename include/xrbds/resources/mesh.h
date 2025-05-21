#ifndef XRBDS_RESOURCES_MESH_H
#define XRBDS_RESOURCES_MESH_H

#include "resource.h"
#include "core/types.h"
#include "resources/texture.h"

#include <vector>

struct FVertex {
  FVector3 position;
  FVector3 normal;
  FVector2 texCoords;

  FVertex(const FVector3 &pos, const FVector3 &norm, const FVector2 &tex)
      : position(pos), normal(norm), texCoords(tex) {}
};

struct FShape {
  TVector<FVertex> vertices;
};

class Mesh : public Resource {
  using Super = Resource;

public:
  static Mesh Load(const TVector<FShape> &shapes,
                   const TVector<FMaterial> &materials,
                   const TVector<PtrShr<Texture>> &textures);

  const TVector<FShape> &getShapes() const { return shapes; }
  const TVector<FMaterial> &getMaterials() const { return materials; }
  const TVector<PtrShr<Texture>> &getTextures() const { return textures; }

private:
  TVector<FShape> shapes;
  TVector<FMaterial> materials;
  TVector<PtrShr<Texture>> textures;

  Mesh() = default;
  Mesh(const TVector<FShape> &shapes, const TVector<FMaterial> &materials,
       const TVector<PtrShr<Texture>> &textures);
};

#endif // XRBDS_RESOURCES_MESH_H
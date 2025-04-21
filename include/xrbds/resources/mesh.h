#ifndef XRBDS_RESOURCES_MESH_H
#define XRBDS_RESOURCES_MESH_H

#include "core/types.h"

#include <vector>

struct Vertex {
  FVector3 position;
  FVector3 normal;
  FVector2 texCoords;

  Vertex(const FVector3 &pos, const FVector3 &norm, const FVector2 &tex)
      : position(pos), normal(norm), texCoords(tex) {}
};

class Mesh {
public:
  static PtrShr<Mesh> Load(std::string path);

  const TVector<Vertex> &getVertices() const;
  const TVector<unsigned int> &getIndices() const;

  void setVertices(const std::vector<Vertex> &vertices);
  void setIndices(const std::vector<unsigned int> &indices);

private:
  TVector<Vertex> m_vertices;
  TVector<unsigned int> m_indices;

  Mesh() = delete;
  Mesh(const Mesh &) = delete;
  Mesh(const TVector<Vertex> &vertices, const TVector<unsigned int> &indices);
};

#endif // XRBDS_RESOURCES_MESH_H
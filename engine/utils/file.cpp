#include "utils/file.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

namespace Utils::File {

FString AssetPath(const FString &path) { return "nitro:/" + path; }

FString ReadTextFile(const FString &path) {
  FString result;
  FILE *f = fopen(AssetPath(path).c_str(), "rb");
  if (!f) {
    iprintf("No se pudo abrir el archivo\n");
  } else {
    iprintf("Archivo abierto\n");

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    rewind(f);

    TVector<uint8_t> buffer(size);
    fread(buffer.data(), 1, size, f);
    fclose(f);

    for (auto &byte : buffer)
      result += byte;
  }

  return std::move(result);
}

TVector<TVector<FVertex>> ReadObjFile(const FString &path) {
  tinyobj::attrib_t attrib;
  TVector<tinyobj::shape_t> shapes;
  TVector<tinyobj::material_t> materials;
  FString err;

  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err,
                              AssetPath(path).c_str(),
                              AssetPath(path + "/..").c_str(), true);

  if (ret)
    iprintf("Cargado correctamente\n");
  else
    iprintf("Error al cargar el archivo: %s\n", err.c_str());

  iprintf("Numero de materiales: %d\n", materials.size());

  TVector<TVector<FVertex>> vertices;

  // Loop over shapes
  for (size_t s = 0; s < shapes.size(); s++) {
    vertices.push_back({});
    // Loop over faces(polygon)
    size_t index_offset = 0;
    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
      size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

      // Loop over vertices in the face.
      for (size_t v = 0; v < fv; v++) {
        // access to vertex
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

        tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
        tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
        tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

        FVector3 positions(vx, vy, vz);

        // Check if `normal_index` is zero or positive. negative = no normal
        // data
        FVector3 normals(0, 0, 0);
        if (idx.normal_index >= 0) {
          tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
          tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
          tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];

          normals = FVector3(nx, ny, nz);
        }

        // Check if `texcoord_index` is zero or positive. negative = no texcoord
        // data
        FVector2 texCoords(0, 0);
        if (idx.texcoord_index >= 0) {
          tinyobj::real_t tx =
              attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
          tinyobj::real_t ty =
              attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];

          texCoords = FVector2(tx, ty);
        }

        vertices[s].push_back(FVertex(positions, normals, texCoords));
      }

      index_offset += fv;

      // per-face material
      // shapes[s].mesh.material_ids[f];
    }
  }

  return std::move(vertices);
}

} // namespace Utils::File

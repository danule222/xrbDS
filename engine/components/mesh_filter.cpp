#include "components/mesh_filter.h"

#include "resources/resource.h"
#include "utils/file.h"

MeshFilter::MeshFilter(const FString &path) {
  // Load the mesh from the file
  auto [shapes, materials] = Utils::File::ReadObjFile(path);

  TVector<PtrShr<Texture>> textures;
  for (const auto &material : materials) {
    auto texture_binary = Utils::File::ReadBinaryFile<unsigned int>(
        path.substr(0, path.find_last_of("/"))
            .append("/")
            .append(material.diffuse_texname.substr(
                0, material.diffuse_texname.find_last_of(".")))
            .append(".img.bin"));

    // auto palette_binary = Utils::File::ReadBinaryFile<unsigned short>(
    //     path.substr(0, path.find_last_of("/"))
    //         .append("/")
    //         .append(material.diffuse_texname.substr(
    //             0, material.diffuse_texname.find_last_of(".")))
    //         .append(".pal.bin"));

    auto palette_binary = TVector<unsigned short>();

    textures.push_back(LoadResource<Texture>(texture_binary, palette_binary));
  }

  mesh = LoadResource<Mesh>(shapes, materials, textures);
}

PtrUnq<MeshFilter> MeshFilter::Initialize(const FString &path) {
  return PtrUnq<MeshFilter>(new MeshFilter(path));
}
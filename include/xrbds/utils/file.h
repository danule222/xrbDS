#ifndef XRBDS_UTILS_FILE_H
#define XRBDS_UTILS_FILE_H

#include "core/types.h"
#include "resources/mesh.h"

struct FObjData {
  TVector<TVector<FVertex>> vertices;
};

namespace Utils::File {

FString AssetPath(const FString &path);

/**
 * @brief Reads the contents of a text file and returns it as a string.
 *
 * @param path The file path to the text file to be read.
 * @return FString The contents of the file as a string.
 * @throws std::runtime_error If the file cannot be opened or read.
 */
FString ReadTextFile(const FString &path);

/**
 * @brief Reads a Wavefront OBJ file and parses its contents into a nested
 * vector of vertices.
 *
 * @param path The file path to the OBJ file as an FString.
 * @return A TVector of TVector of FVertex, where each inner vector represents
 * a group of vertices.
 *
 * @note Ensure the file at the specified path exists and is in a valid OBJ
 * format.
 */
TTuple<TVector<FShape>, TVector<FMaterial>> ReadObjFile(const FString &path);

/**
 * @brief Reads a binary file and returns its contents as a TVector of type T.
 *
 * @tparam T The type of data to read from the binary file.
 * @param path The file path to the binary file to be read.
 * @return TVector<T> A vector containing the contents of the binary file.
 */
template <typename T> TVector<T> ReadBinaryFile(const FString &path) {
  FILE *file = fopen(AssetPath(path).c_str(), "rb");
  if (!file) {
    // TODO: iprintf("Error abriendo: %s\n", path.c_str());
    return {};
  }

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  TVector<T> buffer(size);
  fread(buffer.data(), 1, size, file);
  fclose(file);

  return buffer;
}

} // namespace Utils::File

#endif // XRBDS_UTILS_FILE_H
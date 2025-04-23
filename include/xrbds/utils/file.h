#ifndef XRBDS_UTILS_FILE_H
#define XRBDS_UTILS_FILE_H

#include "core/types.h"
#include "resources/mesh.h"

namespace Utils::File {

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
 * @return A TVector of TVector of FVertex, where each inner vector represents a
 * group of vertices.
 *
 * @note Ensure the file at the specified path exists and is in a valid OBJ
 * format.
 */
TVector<TVector<FVertex>> ReadObjFile(const FString &path);

} // namespace Utils::File

#endif // XRBDS_UTILS_FILE_H
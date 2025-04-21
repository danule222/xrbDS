#include "utils/file.h"

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

} // namespace Utils::File

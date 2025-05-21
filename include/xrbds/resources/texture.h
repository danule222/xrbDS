#ifndef XRBDS_RESOURCES_TEXTURE_H
#define XRBDS_RESOURCES_TEXTURE_H

#include "resource.h"
#include "core/types.h"

/**
 * @class Texture
 * @brief Represents a texture resource that includes pixel data and a color
 * palette.
 *
 * The Texture class is derived from the Resource class and provides
 * functionality to load and manage texture data and its associated palette. It
 * also provides access to the texture's unique identifier.
 */
class Texture : public Resource {
  using Super = Resource;

public:
  virtual ~Texture();

  /**
   * @brief Loads a texture from the given pixel data and palette.
   *
   * @param data A reference to a vector containing the texture's pixel data.
   * @param palette A reference to a vector containing the texture's color
   * palette.
   * @return A Texture object initialized with the provided data and palette.
   */
  static Texture Load(TVector<unsigned int> &data,
                      TVector<unsigned short> &palette);

  /**
   * @brief Retrieves the unique identifier of the texture.
   *
   * @return The unique identifier of the texture as an unsigned 8-bit integer.
   */
  const u8 getId() { return id; }

private:
  Texture(TVector<unsigned int> &data, TVector<unsigned short> &palette);

  int id;
};

#endif // XRBDS_RESOURCES_TEXTURE_H
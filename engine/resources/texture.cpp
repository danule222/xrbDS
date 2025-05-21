#include "resources/texture.h"

#include <nds/arm9/videoGL.h>

Texture::~Texture() {
  // TODO: Check what the hell is happening here
  // glBindTexture(0, id);
  // glColorTableEXT(0, 0, 0, 0, 0, nullptr);
  // glDeleteTextures(1, &id);

  // iprintf("Texture %d deleted\n", id);
}

Texture Texture::Load(TVector<unsigned int> &data,
                      TVector<unsigned short> &palette) {
  return Texture(data, palette);
}

Texture::Texture(TVector<unsigned int> &data, TVector<unsigned short> &palette)
    : Super() {
  glGenTextures(1, &id);
  glBindTexture(0, id);
  // TODO: Manage different texture formats
  glTexImage2D(0, 0, GL_RGBA, TEXTURE_SIZE_128, TEXTURE_SIZE_128, 0,
               TEXGEN_TEXCOORD, (u8 *)data.data());
  // glColorTableEXT(0, 0, 32, 0, 0, (u16 *)palette.data());
}
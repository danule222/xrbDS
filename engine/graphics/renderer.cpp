#include "renderer.h"

#include "core/types.h"
#include "components/mesh_filter.h"
#include "components/transform.h"
#include "resources/mesh.h"
#include <nds.h>
#include <stdio.h>

#include "input/input.h"

PtrUnq<Renderer> Renderer::Instance;

PtrUnq<Renderer> &Renderer::GetInstance() {
  if (!Instance)
    Instance = PtrUnq<Renderer>(new Renderer());

  return Instance;
}

// TEST -------------------
float rotation = 45.f;
// TEST -------------------
void Renderer::beginFrame() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, 256.0 / 192.0, 0.1, 100);
  // glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK);

  // glMatrixMode(GL_TEXTURE);
  // glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); // Load the identity matrix

  // TEST -------------------
  if (Input::IsButtonHeld(EButton::LEFT))
    rotation++;
  if (Input::IsButtonHeld(EButton::RIGHT))
    rotation--;
  // TEST -------------------

  // Render scene
  glTranslatef(0.f, -.75f, -2.f); // Move the camera back
  glRotatef(rotation, 1, 1, 0);   // Rotation
}

void Renderer::render(const Transform &transform,
                      const MeshFilter &meshFilter) {
  glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK);
  glBindTexture(0, meshFilter.getMesh()->getTextures()[0]->getId());
  glBegin(GL_TRIANGLES);

  glColor3b(255, 255, 255);
  for (const auto &shape : meshFilter.getMesh()->getShapes()) {
    for (const auto &vertex : shape.vertices) {
      // glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
      glTexCoord2f(vertex.texCoords.x, vertex.texCoords.y);
      glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
    }
  }

  glEnd();
  glPopMatrix(1);
}

void Renderer::endFrame() {
  glFlush(0); // Flush the rendering pipeline
}

void Renderer::clearScreen() {
  // glClearColor(15, 0, 0, 0); // Clear to black
}

void Renderer::drawCube(float size) {
  glBegin(GL_QUADS);

  // Front face
  glColor3f(1.0, 0.0, 0.0); // Red
  glVertex3f(-size, -size, size);
  glVertex3f(size, -size, size);
  glVertex3f(size, size, size);
  glVertex3f(-size, size, size);

  // Back face
  glColor3f(0.0, 1.0, 0.0); // Green
  glVertex3f(-size, -size, -size);
  glVertex3f(-size, size, -size);
  glVertex3f(size, size, -size);
  glVertex3f(size, -size, -size);

  // Left face
  glColor3f(0.0, 0.0, 1.0); // Blue
  glVertex3f(-size, -size, -size);
  glVertex3f(-size, -size, size);
  glVertex3f(-size, size, size);
  glVertex3f(-size, size, -size);

  // Right face
  glColor3f(1.0, 1.0, 0.0); // Yellow
  glVertex3f(size, -size, -size);
  glVertex3f(size, size, -size);
  glVertex3f(size, size, size);
  glVertex3f(size, -size, size);

  // Top face
  glColor3f(1.0, 0.0, 1.0); // Magenta
  glVertex3f(-size, size, -size);
  glVertex3f(-size, size, size);
  glVertex3f(size, size, size);
  glVertex3f(size, size, -size);

  // Bottom face
  glColor3f(0.0, 1.0, 1.0); // Cyan
  glVertex3f(-size, -size, -size);
  glVertex3f(size, -size, -size);
  glVertex3f(size, -size, size);
  glVertex3f(-size, -size, size);

  glEnd();
  glPopMatrix(1);
}

Renderer::Renderer() {
  // Initialize the video subsystem
  lcdMainOnTop();             // Set the main screen on top
  videoSetMode(MODE_0_3D);    // Set 3D rendering mode
  videoSetModeSub(MODE_5_2D); // Set 2D rendering mode for the sub-screen
  vramSetBankB(VRAM_B_TEXTURE);
  vramSetBankC(VRAM_C_TEXTURE);
  vramSetBankD(VRAM_D_TEXTURE);
  vramSetBankE(VRAM_E_TEX_PALETTE);
  vramSetBankF(VRAM_F_LCD);
  // vramSetBankG(VRAM_G_TEX_PALETTE);

  // Initialize the 3D engine
  glInit();
  glEnable(GL_TEXTURE_2D);
  glViewport(0, 0, 255, 191); // Set viewport
  glEnable(GL_ANTIALIAS);
  glClearColor(0, 0, 0, 31);  // Set clear color (black)
  glClearPolyID(63);          // Set default polygon ID
  glClearDepth(GL_MAX_DEPTH); // Set clear depth
  glEnable(GL_BLEND);

  vramSetBankA(VRAM_A_TEXTURE); // Allocate VRAM for textures
  vramSetBankB(VRAM_B_LCD);

  // Debug
  consoleInit(NULL, 0, BgType_Text4bpp, BgSize_T_256x256, 23, 2, false, true);
  consoleDemoInit();
}

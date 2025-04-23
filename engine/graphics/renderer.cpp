#include "renderer.h"

#include "core/types.h"
#include "components/mesh_filter.h"
#include "components/transform.h"
#include "resources/mesh.h"
#include <nds.h>
#include <stdio.h>

PtrUnq<Renderer> Renderer::Instance;

PtrUnq<Renderer> &Renderer::GetInstance() {
  if (!Instance)
    Instance = PtrUnq<Renderer>(new Renderer());

  return Instance;
}

void Renderer::beginFrame() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, 256.0 / 192.0, 0.1, 100);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix(); // Save the current matrix state

  glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK);

  glLoadIdentity(); // Load the identity matrix

  // Render scene
  glTranslatef(0.f, 0.f, -4.f); // Move the camera back
  glRotatef(45, 1, 1, 0);       // Rotation
}

void Renderer::render(const Transform &transform,
                      const MeshFilter &meshFilter) {
  // drawCube(1.0f); // Draw a cube
  glBegin(GL_TRIANGLES);

  for (const auto &shapes : meshFilter.getMesh()->getVertices()) {
    for (const auto &vertex : shapes) {
      glColor3f(1.0, 0.0, 0.0); // Red
      glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
      glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
      glTexCoord2f(vertex.texCoords.x, vertex.texCoords.y);
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
  lcdMainOnTop();               // Set the main screen on top
  videoSetMode(MODE_0_3D);      // Set 3D rendering mode
  videoSetModeSub(MODE_5_2D);   // Set 2D rendering mode for the sub-screen
  vramSetBankA(VRAM_A_MAIN_BG); // Allocate VRAM for textures

  // Initialize the 3D engine
  glInit();
  glEnable(GL_ANTIALIAS);
  glClearColor(0, 0, 0, 31);  // Set clear color (black)
  glClearPolyID(63);          // Set default polygon ID
  glClearDepth(GL_MAX_DEPTH); // Set clear depth
  glViewport(0, 0, 255, 191); // Set viewport

  // Debug
  consoleDemoInit();
}

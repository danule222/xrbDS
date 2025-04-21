#include "renderer.h"

#include <nds.h>
#include <stdio.h>

std::unique_ptr<Renderer> Renderer::Instance;

std::unique_ptr<Renderer> &Renderer::GetInstance() {
  if (!Instance)
    Instance = std::unique_ptr<Renderer>(new Renderer());

  return Instance;
}

void Renderer::render() {
  clearScreen();    // Clear the screen
  beginFrame();     // Prepare for rendering
  glLoadIdentity(); // Load the identity matrix

  // Render scene
  glTranslatef(0.f, 0.f, -4.f); // Move the camera back
  glRotatef(45, 1, 1, 0);       // Rotation
  drawCube(1.0f);               // Draw a cube

  endFrame(); // Finish rendering
}

void Renderer::beginFrame() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, 256.0 / 192.0, 0.1, 100);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix(); // Save the current matrix state

  glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK);
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

#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

class Renderer {
public:
  virtual ~Renderer() = default;

  static std::unique_ptr<Renderer> Create();

  void render();

private:
  void beginFrame();

  void endFrame();

  void clearScreen();

  void drawCube(float size);

  Renderer();
};

#endif // RENDERER_H
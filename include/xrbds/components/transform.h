#ifndef XRBDS_COMPONENTS_TRANSFORM_H
#define XRBDS_COMPONENTS_TRANSFORM_H

#include <glm/glm.hpp>

using Vector3 = glm::vec3;
using Vector2 = glm::vec2;

struct Transform {
  Vector3 position{0.0f, 0.0f, 0.0f};
  Vector3 rotation{0.0f, 0.0f, 0.0f}; // Euler angles in radians
  Vector3 scale{1.0f, 1.0f, 1.0f};

  Transform() = default;

  Transform(const Vector3 &pos, const Vector3 &rot, const Vector3 &scl)
      : position(pos), rotation(rot), scale(scl) {}
};

#endif // XRBDS_COMPONENTS_TRANSFORM_H
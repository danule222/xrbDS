#ifndef XRBDS_COMPONENTS_TRANSFORM_H
#define XRBDS_COMPONENTS_TRANSFORM_H

#include "component.h"
#include "core/types.h"

struct Transform : public Component {
  FVector3 position{0.0f, 0.0f, 0.0f};
  FVector3 rotation{0.0f, 0.0f, 0.0f}; // Euler angles in radians
  FVector3 scale{1.0f, 1.0f, 1.0f};

  Transform(const FVector3 &pos, const FVector3 &rot, const FVector3 &scl)
      : position(pos), rotation(rot), scale(scl) {}
};

#endif // XRBDS_COMPONENTS_TRANSFORM_H
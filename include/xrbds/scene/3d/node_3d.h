#ifndef XRBDS_SCENE_3D_NODE_3D_H
#define XRBDS_SCENE_3D_NODE_3D_H

#include "scene/node.h"

struct Node3D : public Node {
  using Super = Node;

public:
  Node3D();
};

#endif // XRBDS_SCENE_3D_NODE_3D_H
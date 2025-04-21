#ifndef XRBDS_SCENE_3D_NODE_3D_H
#define XRBDS_SCENE_3D_NODE_3D_H

class Node3D {
public:
  Node3D();
  virtual ~Node3D();

  // Set and get position
  void setPosition(float x, float y, float z);
  void getPosition(float &x, float &y, float &z) const;

  // Set and get rotation
  void setRotation(float pitch, float yaw, float roll);
  void getRotation(float &pitch, float &yaw, float &roll) const;

  // Set and get scale
  void setScale(float x, float y, float z);
  void getScale(float &x, float &y, float &z) const;

private:
  float position[3];
  float rotation[3];
  float scale[3];
};

#endif // XRBDS_SCENE_3D_NODE_3D_H
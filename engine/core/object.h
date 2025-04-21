#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
  Object();
  virtual ~Object();

  virtual void update();
  virtual void render();

  virtual void test() { iprintf("Object::test\n"); };

protected:
  int id;
};

#endif // OBJECT_H
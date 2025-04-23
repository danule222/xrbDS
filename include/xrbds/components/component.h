#ifndef COMPONENT_H
#define COMPONENT_H

#include "core/types.h"

struct Component {
public:
  static PtrUnq<Component> Initialize();
};

#endif // COMPONENT_H
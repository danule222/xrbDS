#include "components/component.h"

PtrUnq<Component> Component::Initialize() {
  return PtrUnq<Component>(new Component());
}
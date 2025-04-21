#include "component_manager.h"

PtrUnq<ComponentManager> ComponentManager::Instance;

PtrUnq<ComponentManager> &ComponentManager::GetInstance() {
  if (!Instance)
    Instance = PtrUnq<ComponentManager>(new ComponentManager());

  return Instance;
}
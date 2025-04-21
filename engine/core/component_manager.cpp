#include "component_manager.h"

std::unique_ptr<ComponentManager> ComponentManager::Instance;

std::unique_ptr<ComponentManager> &ComponentManager::GetInstance() {
  if (!Instance)
    Instance = std::unique_ptr<ComponentManager>(new ComponentManager());

  return Instance;
}
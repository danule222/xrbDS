#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>
#include <stdexcept>
#include <unordered_set>
#include <cstdint>

#include <calico/types.h>

#define Entity u32

class ComponentManager {
public:
  ~ComponentManager() = default;

  static std::unique_ptr<ComponentManager> &GetInstance();

  Entity newEntity() {
    Entity entityID = nextEntityID++;
    activeEntities.insert(entityID);
    return entityID;
  }

  void removeEntity(Entity entityID) {
    if (activeEntities.erase(entityID) > 0) {
      removeAllComponents(entityID);
    }
  }

  template <typename ComponentType>
  void addComponent(Entity entityID, const ComponentType &component) {
    auto &componentMap = getComponentMap<ComponentType>();
    componentMap[entityID] =
        std::make_shared<ComponentType>(std::move(component));
  }

  template <typename ComponentType>
  std::shared_ptr<ComponentType> getComponent(Entity entityID) {
    auto &componentMap = getComponentMap<ComponentType>();
    auto it = componentMap.find(entityID);
    if (it != componentMap.end()) {
      return it->second;
    }
    return nullptr;
  }

  template <typename ComponentType> void removeComponent(Entity entityID) {
    auto &componentMap = getComponentMap<ComponentType>();
    componentMap.erase(entityID);
  }

  void removeAllComponents(Entity entityID) {
    for (auto &pair : componentPools) {
      pair.second->remove(entityID);
    }
  }

  template <typename ComponentType> auto begin() {
    return getComponentMap<ComponentType>().begin();
  }

  template <typename ComponentType> auto end() {
    return getComponentMap<ComponentType>().end();
  }

private:
  ComponentManager() = default;

  ComponentManager(const ComponentManager &) = delete;
  ComponentManager &operator=(const ComponentManager &) = delete;

  static std::unique_ptr<ComponentManager> Instance;

  struct IComponentPool {
    virtual ~IComponentPool() = default;
    virtual void remove(Entity entityID) = 0;
  };

  template <typename ComponentType> struct ComponentPool : IComponentPool {
    std::unordered_map<Entity, std::shared_ptr<ComponentType>> components;

    void remove(Entity entityID) override { components.erase(entityID); }
  };

  template <typename ComponentType>
  std::unordered_map<Entity, std::shared_ptr<ComponentType>> &
  getComponentMap() {
    std::type_index typeIndex(typeid(ComponentType));
    if (componentPools.find(typeIndex) == componentPools.end()) {
      componentPools[typeIndex] =
          std::make_unique<ComponentPool<ComponentType>>();
    }
    return static_cast<ComponentPool<ComponentType> *>(
               componentPools[typeIndex].get())
        ->components;
  }

  std::unordered_map<std::type_index, std::unique_ptr<IComponentPool>>
      componentPools;
  std::unordered_set<Entity> activeEntities;
  Entity nextEntityID = 0;
};

#endif // COMPONENT_MANAGER_H
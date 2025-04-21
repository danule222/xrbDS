#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>
#include <stdexcept>
#include <unordered_set>
#include <cstdint>

#include "core/types.h"

class ComponentManager {
public:
  ~ComponentManager() = default;

  static PtrUnq<ComponentManager> &GetInstance();

  FEntity newEntity() {
    FEntity entityID = nextEntityID++;
    activeEntities.insert(entityID);
    return entityID;
  }

  void removeEntity(FEntity entityID) {
    if (activeEntities.erase(entityID) > 0) {
      removeAllComponents(entityID);
    }
  }

  template <typename ComponentType>
  void addComponent(FEntity entityID, const ComponentType component) {
    auto &componentMap = getComponentMap<ComponentType>();
    componentMap[entityID] =
        std::make_shared<ComponentType>(std::move(component));
  }

  template <typename ComponentType>
  PtrShr<ComponentType> getComponent(FEntity entityID) {
    auto &componentMap = getComponentMap<ComponentType>();
    auto it = componentMap.find(entityID);
    if (it != componentMap.end()) {
      return it->second;
    }
    return nullptr;
  }

  template <typename ComponentType> void removeComponent(FEntity entityID) {
    auto &componentMap = getComponentMap<ComponentType>();
    componentMap.erase(entityID);
  }

  void removeAllComponents(FEntity entityID) {
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

  template <typename... Components>
  TVector<std::tuple<FEntity, Components *...>> view() {
    TVector<std::tuple<FEntity, Components *...>> result;

    if constexpr (sizeof...(Components) == 0)
      return result;

    auto &baseMap =
        getComponentMap<std::tuple_element_t<0, std::tuple<Components...>>>();

    for (auto &[entityID, baseComp] : baseMap) {
      if ((getComponent<Components>(entityID) && ...)) {
        result.emplace_back(entityID,
                            getComponent<Components>(entityID).get()...);
      }
    }

    return result;
  }

private:
  ComponentManager() = default;

  ComponentManager(const ComponentManager &) = delete;
  ComponentManager &operator=(const ComponentManager &) = delete;

  struct IComponentPool {
    virtual ~IComponentPool() = default;
    virtual void remove(FEntity entityID) = 0;
  };

  static PtrUnq<ComponentManager> Instance;
  std::unordered_map<std::type_index, PtrUnq<IComponentPool>> componentPools;
  std::unordered_set<FEntity> activeEntities;
  FEntity nextEntityID = 0;

  template <typename ComponentType> struct ComponentPool : IComponentPool {
    std::unordered_map<FEntity, PtrShr<ComponentType>> components;

    void remove(FEntity entityID) override { components.erase(entityID); }
  };

  template <typename ComponentType>
  std::unordered_map<FEntity, PtrShr<ComponentType>> &getComponentMap() {
    std::type_index typeIndex(typeid(ComponentType));
    if (componentPools.find(typeIndex) == componentPools.end()) {
      componentPools[typeIndex] =
          std::make_unique<ComponentPool<ComponentType>>();
    }
    return static_cast<ComponentPool<ComponentType> *>(
               componentPools[typeIndex].get())
        ->components;
  }
};

#endif // COMPONENT_MANAGER_H
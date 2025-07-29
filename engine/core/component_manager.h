/**
 * @file component_manager.h
 * @brief Header file for the ComponentManager class.
 * @copyright 2025 Daniel Ramirez Morilla
 *
 * This file contains the declaration of the Renderer class, which serves as
 * a base class for rendering operations. The Renderer class provides an
 * interface for managing frames, clearing the screen, and drawing objects.
 *
 * The class follows the singleton design pattern, ensuring that only one
 * instance of the Renderer exists throughout the application. It includes
 * methods for rendering frames, preparing and finalizing the rendering
 * process, and drawing graphical objects such as cubes.
 *
 * Usage:
 * - Use GetInstance() to access the singleton instance.
 * - Use newEntity() to create a new entity.
 * - Use addComponent/removeComponent/getComponent to manage components for
 * entities.
 * - Use view<Components...>() to iterate over entities that have all specified
 * components.
 *
 * @author Daniel Ramirez Morilla
 * @date 2025-04-19
 */

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

/**
 * @class ComponentManager
 * @brief Manages entities and their associated components in an ECS
 * (Entity-Component-System) architecture.
 *
 * This singleton class provides functionality to create and remove entities,
 * add/remove/query components, and iterate over entities with specific
 * component combinations. Components are stored in type-erased pools, allowing
 * for efficient management and retrieval.
 */
class ComponentManager {
public:
  ~ComponentManager() = default;

  /**
   * @brief PtrUnq to the singleton instance of ComponentManager.
   *
   * @return PtrUnq<ComponentManager> & - Reference to the singleton instance.
   */
  static PtrUnq<ComponentManager> &GetInstance();

  /**
   * @brief Creates a new entity.
   *
   * @return New entity ID.
   */
  FEntity newEntity() {
    FEntity entityID = nextEntityID++;
    activeEntities.insert(entityID);
    return entityID;
  }

  /**
   * @brief Removes an entity and all its associated components.
   *
   * @param entityID The ID of the entity to remove.
   */
  void removeEntity(FEntity entityID) {
    if (activeEntities.erase(entityID) > 0) {
      removeAllComponents(entityID);
    }
  }

  /**
   * @brief Adds a component to an entity.
   *
   * @tparam ComponentType Component to be added to the entity.
   * @param entityID Entity where the component will be added.
   * @param component Component instance to be added.
   */
  template <typename ComponentType>
  void addComponent(FEntity entityID, const ComponentType component) {
    auto &componentMap = getComponentMap<ComponentType>();
    componentMap[entityID] =
        std::make_shared<ComponentType>(std::move(component));
  }

  /**
   * @brief Gets the instance of the specified component type for an entity.
   *
   * @tparam ComponentType Component type to retrieve.
   * @param entityID Entity.
   * @return PtrShr<ComponentType> PtrShr to the component instance. Returns
   * nullptr if it does not exist.
   */
  template <typename ComponentType>
  PtrShr<ComponentType> getComponent(FEntity entityID) {
    auto &componentMap = getComponentMap<ComponentType>();
    auto it = componentMap.find(entityID);
    if (it != componentMap.end()) {
      return it->second;
    }
    return nullptr;
  }

  /**
   * @brief Removes a component from an entity.
   *
   * @tparam ComponentType
   * @param entityID
   */
  template <typename ComponentType> void removeComponent(FEntity entityID) {
    auto &componentMap = getComponentMap<ComponentType>();
    componentMap.erase(entityID);
  }

  /**
   * @brief Removes all components associated with an entity.
   *
   * @param entityID The ID of the entity whose components will be removed.
   */
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

  /**
   * @brief Returns a vector of tuples containing entity IDs and pointers to
   * components of the specified types.
   *
   * This function allows querying entities that have all specified components.
   * It returns a vector of tuples, where each tuple contains an entity ID and
   * pointers to the components of the specified types.
   *
   * @tparam Components... Variadic template parameter pack representing the
   * component types to be included in the view.
   * @return TVector<std::tuple<FEntity, Components *...>> A vector of tuples
   * containing entity IDs and pointers to the components.
   */
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
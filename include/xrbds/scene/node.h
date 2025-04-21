#ifndef XRBDS_SCENE_NODE_H
#define XRBDS_SCENE_NODE_H

#include "core/types.h"
#include "core/component_manager.h"

/**
 * @brief Creates a new shared pointer to a node of type T, forwarding the
 * provided arguments to the constructor.
 *
 * @tparam T The type of the node to be created.
 * @tparam Args The types of the arguments to be forwarded to the constructor of
 * T.
 * @param args The arguments to be forwarded to the constructor of T.
 * @return PtrShr<T> A shared pointer to the newly created node of type T.
 */
template <typename T, typename... Args> PtrShr<T> NewNode(Args &&...args) {
  auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
  return ptr;
}

/**
 * @brief Represents a node in the scene graph.
 *
 * The Node class serves as a base structure for elements in the scene graph.
 * It contains an identifier for the entity it represents.
 */
struct Node {
public:
  Node();

  template <typename T> PtrShr<T> getComponent() {
    return ComponentManager::GetInstance()->getComponent<T>(id);
  }

protected:
  FEntity id;
};

#endif // XRBDS_SCENE_NODE_H
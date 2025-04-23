#ifndef RESOURCE_H
#define RESOURCE_H

#include "core/types.h"
#include <stdio.h>

/**
 * @struct FResourceData
 * @brief Represents resource data with a name and a file path.
 *
 * This structure is used to store information about a resource, including
 * its name and the path to its location.
 *
 * @var FResourceData::name
 * The name of the resource.
 *
 * @var FResourceData::path
 * The file path to the resource.
 *
 * @param name The name of the resource.
 * @param path The file path to the resource.
 */
struct FResourceData {
  /**
   * @brief Constructs an FResourceData object with the specified name and path.
   *
   * @param name The name of the resource.
   * @param path The file path of the resource.
   */
  FResourceData(const FString &name, const FString &path)
      : name(name), path(path) {}

  FString name;
  FString path;
};

/**
 * @class Resource
 * @brief Represents a resource that encapsulates data of type FResourceData.
 *
 * This class is used to manage and store resource data. It provides a
 * constructor to initialize the resource with the given data.
 *
 * @note The class currently only stores the data and does not provide any
 *       additional functionality or accessors.
 */
class Resource {
public:
  static Resource Load();

protected:
  Resource() = default;
};

/**
 * @brief Loads a resource by creating a shared pointer to an instance of the
 * specified type.
 *
 * @tparam T The type of the resource to be loaded. Must be constructible
 with
 * the provided arguments.
 * @tparam Args The types of the arguments to be forwarded to the constructor
 of
 * T.
 * @param args The arguments to be forwarded to the constructor of T.
 * @return PtrShr<T> A shared pointer to the newly created instance of T.
 *
 * @note This function uses perfect forwarding to pass the arguments to the
 * constructor of T. Ensure that the type T is compatible with the provided
 * arguments.
 */
template <typename T, typename... Args> PtrShr<T> LoadResource(Args &&...args) {
  if constexpr (!std::is_base_of<Resource, T>::value) {
    iprintf("Error: Type T must be derived from Resource.\n");
    return nullptr;
  }

  auto ptr = std::make_shared<T>(T::Load(std::forward<Args>(args)...));

  return ptr;
}

#endif // RESOURCE_H
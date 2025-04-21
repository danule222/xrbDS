/**
 * @file types.h
 * @brief Core type definitions and aliases for the xrbDS project.
 * @copyright 2025 Daniel Ramirez Morilla
 *
 * This header file provides a collection of type aliases and templates
 * to simplify and standardize the usage of common data structures,
 * memory management utilities, and mathematical vector types.
 *
 * @author Daniel Ramirez Morilla
 * @date 2025-04-21
 */

#ifndef XRBDS_CORE_TYPES_H
#define XRBDS_CORE_TYPES_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <bits/unique_ptr.h>
#include <bits/shared_ptr.h>
#include <calico/types.h>
#include <array>
#include <vector>
#include <string>

/////////////////////////////////////
// MEMORY
/////////////////////////////////////

/**
 * @brief Alias template for std::unique_ptr.
 *
 * This alias simplifies the usage of std::unique_ptr by providing a shorter and
 * more concise name. It is a smart pointer that owns and manages the lifetime
 * of a dynamically allocated object.
 *
 * @tparam T The type of the object to manage.
 */
template <typename T> using PtrUnq = std::unique_ptr<T>;
/**
 * @brief Alias template for std::shared_ptr.
 *
 * This alias simplifies the usage of std::shared_ptr by providing a shorter and
 * more concise name. It is a smart pointer that owns and manages the lifetime
 * of a dynamically allocated object.
 *
 * @tparam T The type of the object to manage.
 */
template <typename T> using PtrShr = std::shared_ptr<T>;

/////////////////////////////////////
// DATA STRUCTURES
/////////////////////////////////////

/**
 * @brief Alias template for std::vector.
 *
 * This alias simplifies the usage of `std::vector` by providing a shorthand
 * for defining vectors with a specific type.
 *
 * @tparam T The type of the elements in the vector.
 */
template <typename T> using TVector = std::vector<T>;
/**
 * @brief Alias template for std::array.
 *
 * This alias simplifies the usage of `std::array` by providing a shorthand
 * for defining arrays with a fixed size and a specific type.
 *
 * @tparam T The type of the elements in the array.
 * @tparam S The size of the array.
 */
template <typename T, size_t S> using TArray = std::array<T, S>;

/////////////////////////////////////
// BASIC TYPES
/////////////////////////////////////

/**
 * @typedef FString
 * @brief Alias for the standard C++ string type (std::string).
 *
 * This type alias is used to represent a string in the application, providing
 * a more descriptive or domain-specific name for std::string.
 */
using FString = std::string;
/**
 * @typedef FEntity
 * @brief Alias for a 32-bit signed integer type (int32_t).
 *
 * This type is used to represent integer values in the application.
 */
using FEntity = u32;

/////////////////////////////////////
// VECTORS
/////////////////////////////////////

/**
 * @typedef FVector2
 * @brief Alias for a 2D vector type provided by the glm library.
 *
 * This type represents a 2-dimensional vector, typically used for
 * mathematical operations involving 2D space, such as positions,
 * directions, or velocities.
 *
 * @see glm::vec2
 */
using FVector2 = glm::vec2;
/**
 * @typedef FVector2Int
 * @brief Alias for a 2D integer vector type provided by the glm library.
 *
 * This type represents a 2-dimensional vector, typically used for
 * mathematical operations involving 2D space, such as positions,
 * directions, or velocities.
 *
 * @see glm::ivec2
 */
using FVector2Int = glm::ivec2;
/**
 * @typedef FVector3
 * @brief Alias for a 3D vector type provided by the glm library.
 *
 * This type represents a 3-dimensional vector, typically used for
 * mathematical operations involving 3D space, such as positions,
 * directions, or velocities.
 *
 * @see glm::vec3
 */
using FVector3 = glm::vec3;
/**
 * @typedef FVector3Int
 * @brief Alias for a 3D integer vector type provided by the glm library.
 *
 * This type represents a 3-dimensional vector, typically used for
 * mathematical operations involving 3D space, such as positions,
 * directions, or velocities.
 *
 * @see glm::ivec3
 */
using FVector3Int = glm::ivec3;

#endif // XRBDS_CORE_TYPES_H
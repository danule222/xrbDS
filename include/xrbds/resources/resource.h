#ifndef RESOURCE_H
#define RESOURCE_H

#include "core/types.h"
#include <stdio.h>

template <typename T, typename... Args> PtrShr<T> LoadResource(Args &&...args) {
  auto ptr = std::make_shared<T>(std::forward<Args>(args)...);

  return ptr;
}

class Resource {
public:
  Resource(const FString &name, const FString &path);

private:
  FString name;
  FString path;
};

#endif // RESOURCE_H
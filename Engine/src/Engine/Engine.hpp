#pragma once

#include <memory>
#include <string>
#include <spdlog/spdlog.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <glm/glm.hpp>

#include "Core/Logger.hpp"


template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename ... Args>
constexpr Ref<T> MakeRef(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}


using std::string;

using UInt = unsigned int;

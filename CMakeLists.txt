cmake_minimum_required(VERSION 3.23)
if(NOT DEFINED ENV{VCPKG_ROOT})
message(FATAL_ERROR "VCPKG_ROOT is not defined")
else()
message(STATUS "VCPKG_ROOT is $ENV{VCPKG_ROOT}")
endif()


set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
message(STATUS "CMAKE_TOOLCHAIN_FILE is ${CMAKE_TOOLCHAIN_FILE}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_GENERATOR_PLATFORM x64)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(VCPKG_TARGET_TRIPLET "x64-windows")


project("Root")

find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)


add_subdirectory("Vendor/imgui")
add_subdirectory("Engine")
add_subdirectory("Game")

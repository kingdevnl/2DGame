cmake_minimum_required(VERSION 3.23)
project(Engine)


file(GLOB_RECURSE engine_source "src/Engine/*.h" "src/Engine/*.hpp" "src/Engine/*.cpp" "src/Vendor/stb_image.h")

add_library(Engine ${engine_source})

target_link_libraries(Engine PUBLIC spdlog::spdlog spdlog::spdlog_header_only glfw GLEW::GLEW glm::glm EnTT::EnTT imgui)

target_include_directories(Engine PRIVATE "../Vendor/imgui")
target_include_directories(Engine PRIVATE "./src")

if(WIN32)
    target_compile_options(Engine PRIVATE "/MP")
endif()
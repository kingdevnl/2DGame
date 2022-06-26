cmake_minimum_required(VERSION 3.23)
project(Engine)


file(GLOB_RECURSE engine_source "Engine/*.h" "Engine/*.hpp" "Engine/*.cpp" "Vendor/stb_image.h")

add_library(Engine ${engine_source})

target_link_libraries(Engine PUBLIC spdlog::spdlog spdlog::spdlog_header_only glfw GLEW::GLEW glm::glm EnTT::EnTT imgui)

include_directories(Engine "../Vendor/imgui")


target_compile_options(Engine PRIVATE "/MP")

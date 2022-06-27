project(ImGui)


file(GLOB_RECURSE imgui_source "imgui/*.h" "imgui/*.hpp" "imgui/*.cpp")


find_package(glfw3 CONFIG REQUIRED)
add_library(imgui ${imgui_source})
target_link_libraries(imgui PRIVATE glfw)

if(WIN32)
    target_compile_options(imgui PRIVATE "/MP")
endif()
project(ImGui)


file(GLOB_RECURSE imgui_source "imgui/*.h" "imgui/*.hpp" "imgui/*.cpp")



add_library(imgui ${imgui_source})

target_compile_options(imgui PRIVATE "/MP")

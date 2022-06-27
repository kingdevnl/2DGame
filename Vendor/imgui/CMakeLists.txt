project(ImGui)


file(GLOB_RECURSE imgui_source "imgui/*.h" "imgui/*.hpp" "imgui/*.cpp")



add_library(imgui ${imgui_source})

if(WIN32)
    target_compile_options(imgui PRIVATE "/MP")
endif()
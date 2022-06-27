project(Engine)

include_directories(../Engine)

file(GLOB_RECURSE game_source "Game/*.h" "Game/*.hpp" "Game/*.cpp")
file(GLOB_RECURSE assets_files "Assets/*.glsl" "assets/*.png" "assets/*.lua")

add_executable(Game ${game_source})

target_link_libraries(Game Engine )
add_custom_target(Game_Assets SOURCES ${assets_files})


set_target_properties(
    Game PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Game")
    
    
target_include_directories(Game PRIVATE "../Engine/src/" "../Vendor/imgui")

file(COPY Assets DESTINATION ${PROJECT_BINARY_DIR})

if(WIN32)
    target_compile_options(Game PRIVATE "/MP")
endif()
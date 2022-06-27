#pragma once
#include <GLFW/glfw3.h>


namespace Engine::Input
{
    static bool IsKeyDown(int key)
    {
        const auto state = glfwGetKey(glfwGetCurrentContext(), key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
}

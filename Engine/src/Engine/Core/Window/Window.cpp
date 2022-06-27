#include "Window.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Core/Application/Application.hpp"
#include "Engine/Core/Event/Events.hpp"

#include <gl/glew.h>
#include <GLFW/glfw3.h>


namespace Engine
{
    void Window::Create()
    {
        INFO("Creating window {} {}x{}", title, width, height);
        glfwInit();
        glfwDefaultWindowHints();
        this->handle = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(this->handle);
        glewInit();

        glfwSetWindowUserPointer(this->handle, this);

        glfwSetWindowSizeCallback(this->handle, [](GLFWwindow* window, int width, int height)
        {
            auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            win->width = width;
            win->height = height;
            glViewport(0, 0, width, height);
            auto event = WindowResizeEvent(width, height);
            Application::Get()->OnEvent(event);
        });
        
        glfwSetKeyCallback(this->handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (action == GLFW_PRESS)
            {
                auto event = KeyPressEvent(key, scancode);
                Application::Get()->OnEvent(event);
            }
        });
        
        //scroll callback
        glfwSetScrollCallback(this->handle, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            auto event = MouseScrollEvent(xoffset, yoffset);
            Application::Get()->OnEvent(event);
        });


        auto monitor = glfwGetPrimaryMonitor();
        auto mode = glfwGetVideoMode(monitor);
        glfwSetWindowPos(this->handle, (mode->width - this->width) / 2, (mode->height - this->height) / 2);

        //disable vsync
        glfwSwapInterval(0);
    }

    void Window::Update()
    {
        glfwPollEvents();
    }

    void Window::SetTitle(string title)
    {
        glfwSetWindowTitle(this->handle, title.c_str());
    }

    void Window::Destroy()
    {
        glfwDestroyWindow(this->handle);
        glfwTerminate();
    }
}

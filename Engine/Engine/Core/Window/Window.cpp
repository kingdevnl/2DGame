#include "Window.hpp"
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "../App.hpp"
#include "../Event/Events.hpp"

namespace Engine
{
    void Window::Create()
    {
        DEBUG("Creating window {} {}x{}", title, width, height);
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

            auto event = Events::WindowResizeEvent(width, height);
            Application::app->OnEvent(event);
        });

        glfwSetKeyCallback(this->handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            auto event = Events::KeyEvent(key, action, mods);
            Application::app->OnEvent(event);
        });

        //scroll callback
        glfwSetScrollCallback(this->handle, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            auto event = Events::MouseScrollEvent(xoffset, yoffset);
            Application::app->OnEvent(event);
        });

        // center the window

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

#pragma once
#include "../../Engine.hpp"

struct GLFWwindow;


namespace Engine
{
    class Window
    {
    private:
        int width, height;
        string title;
        GLFWwindow* handle;

    public:
        Window(int width, int height, string title)
            : width(width),
              height(height),
              title(title)
        {
        }


        void Create();
        void Update();
        void SetTitle(string title);
        void Destroy();

        int GetWidth() const { return width; }
        int GetHeight() const { return height; }
        string GetTitle() const { return title; }

        GLFWwindow* GetHandle() const { return handle; }
    };
}

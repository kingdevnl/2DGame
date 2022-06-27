#pragma once

#include "Event.hpp"

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Engine
{
    class KeyPressEvent : public Event
    {
    public:
        const int key, scancode;

        explicit KeyPressEvent(int key, int scancode)
            : key(key), scancode(scancode)
        {
        }

        EVENT_CLASS_TYPE(KEY_PRESSED)
    };

    class MouseScrollEvent : public Event
    {
    public:
        const double xOffset, yOffset;

        explicit MouseScrollEvent(double xOffset, double yOffset)
            : xOffset(xOffset), yOffset(yOffset)
        {
        }

        EVENT_CLASS_TYPE(MOUSE_SCROLL)
    };

    class WindowResizeEvent : public Event
    {
    public:
        const int width, height;

        explicit WindowResizeEvent(int width, int height)
            : width(width), height(height)
        {
        }

        EVENT_CLASS_TYPE(WINDOW_RESIZE)
    };
}

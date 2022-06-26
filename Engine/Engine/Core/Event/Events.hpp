#pragma once

#include "Event.hpp"


namespace Engine::Events
{
    class KeyEvent : public Event
    {
    public:
        const int key;
        const int action;
        const int mods;

        explicit KeyEvent(int key, int action, int mods)
            : Event(EventType::KEY_EVENT)
              , key(key), action(action), mods(mods)
        {
        }
    };

    class WindowResizeEvent : public Event
    {
    public:
        const int width, height;

        explicit WindowResizeEvent(int width, int height)
            : Event(EventType::WINDOW_RESIZE_EVENT),
              width(width),
              height(height)
        {
        }
    };

    class MouseScrollEvent : public Event
    {
    public:
        const double xOffset, yOffset;

        explicit MouseScrollEvent(double xOffset, double yOffset)
            : Event(EventType::MOUSE_SCROLL_EVENT),
              xOffset(xOffset),
              yOffset(yOffset)
        {
        }
    };
}

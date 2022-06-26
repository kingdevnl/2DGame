#pragma once

namespace Engine
{
    namespace EventType
    {
        enum EventType
        {
            KEY_EVENT = 0,
            MOUSE_SCROLL_EVENT = 1,
            WINDOW_RESIZE_EVENT = 2
        };
    }

    class Event
    {
    public:
        EventType::EventType type;

        Event(EventType::EventType type) : type(type)
        {
        }
    };
}

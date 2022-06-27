#pragma once

#include <functional>


namespace Engine
{
    enum class EventType
    {
        NONE = 0,
        KEY_PRESSED,
        WINDOW_RESIZE,
        MOUSE_SCROLL
    };

    
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }\
virtual const char* GetName() const override { return #type; }

    class Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }
        
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {
        }
		
        // F will be deduced by the compiler
        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled |= func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}
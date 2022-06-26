#include "../../Engine.hpp"


namespace Engine::Math
{
    inline float Clamp(float value, float min, float max)
    {
        return std::min(std::max(value, min), max);
    }

    inline int Clamp(int value, int min, int max)
    {
        return std::min(std::max(value, min), max);
    }
}

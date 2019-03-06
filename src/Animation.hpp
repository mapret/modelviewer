#pragma once

#include "math/quat.hpp"
#include "math/vec3.hpp"
#include <map>
#include <string>


struct Animation
{
    struct Keyframes
    {
        std::map<float, vec3> position_keyframes;
        std::map<float, vec3> scale_keyframes;
        std::map<float, quat> rotation_keyframes;
    };

    std::string name;
    float duration;
    std::map<size_t, Keyframes> keyframes;
};

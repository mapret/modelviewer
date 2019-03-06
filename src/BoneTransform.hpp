#pragma once

#include "math/mat4.hpp"
#include <vector>


class BoneTransform
{
  public:
    void setNumberOfBones(size_t n);
    void setTransform(size_t index, const mat4& transform);
    void setCurrentAnimationIndex(size_t index);
    void setRunning(bool running);
    void resetAnimation();

    const mat4& getTransform(size_t index) const;
    size_t getCurrentAnimationIndex() const;
    bool isAnimationActive() const;
    float& getAnimationTime();
    bool getRunning() const;

    const static size_t npos = static_cast<size_t>(-1);

  private:
    std::vector<mat4> transforms_;
    float animation_time_ = 0;
    size_t current_animation_index_ = npos;
    bool running_ = true;
};

#include "BoneTransform.hpp"


void BoneTransform::setNumberOfBones(size_t n)
{
  transforms_.resize(n);
}

void BoneTransform::setTransform(size_t index, const mat4& transform)
{
  transforms_[index] = transform;
}

void BoneTransform::setCurrentAnimationIndex(size_t index)
{
  current_animation_index_ = index;
}

void BoneTransform::setRunning(bool running)
{
  running_ = running;
}

void BoneTransform::resetAnimation()
{
  animation_time_ = 0;
}

const mat4& BoneTransform::getTransform(size_t index) const
{
  if (current_animation_index_ == npos)
  {
    static const mat4 identity;
    return identity;
  }
  return transforms_[index];
}

size_t BoneTransform::getCurrentAnimationIndex() const
{
  return current_animation_index_;
}

bool BoneTransform::isAnimationActive() const
{
  return current_animation_index_ != npos;
}

float& BoneTransform::getAnimationTime()
{
  return animation_time_;
}

bool BoneTransform::getRunning() const
{
  return running_;
}

#include "Bone.hpp"


void Bone::setName(std::string&& name)
{
  name_ = std::move(name);
}

void Bone::setNodeOffset(mat4&& matrix)
{
  node_offset_ = std::move(matrix);
}

void Bone::setBoneOffset(mat4&& matrix)
{
  bone_offset_ = std::move(matrix);
}

void Bone::addChildIndex(size_t index)
{
  child_indices_.push_back(index);
}

const std::string& Bone::getName() const
{
  return name_;
}

const mat4& Bone::getNodeOffset() const
{
  return node_offset_;
}

const mat4& Bone::getBoneOffset() const
{
  return bone_offset_;
}

const std::vector<size_t>& Bone::getChildIndices() const
{
  return child_indices_;
}

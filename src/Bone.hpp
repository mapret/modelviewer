#pragma once

#include "math/mat4.hpp"
#include <cstddef>
#include <string>


class Bone
{
  public:
    void setName(std::string&& name);
    void setNodeOffset(mat4&& matrix);
    void setBoneOffset(mat4&& matrix);
    void addChildIndex(size_t index);

    const std::string& getName() const;
    const mat4& getNodeOffset() const;
    const mat4& getBoneOffset() const;
    const std::vector<size_t>& getChildIndices() const;

  private:
    std::string name_;
    mat4 node_offset_;
    mat4 bone_offset_;
    std::vector<size_t> child_indices_;
};

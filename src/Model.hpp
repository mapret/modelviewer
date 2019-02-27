#pragma once

#include "Bone.hpp"
#include "Mesh.hpp"
#include <filesystem>


class Model
{
  public:
    bool import(const std::filesystem::path& path);

    void addBone(Bone&& bone);
    void addMesh(Mesh&& mesh);

    size_t getBoneCount() const;
    size_t getBoneIndex(const std::string& name) const;
    const Bone& getBone(size_t index) const;
    Bone& getBone(size_t index);
    const std::vector<Mesh>& getMeshes() const;

    static const size_t	npos = static_cast<size_t>(-1);

  private:
    std::vector<Bone> bones_;
    std::unordered_map<std::string, size_t> bone_names_;
    std::vector<Mesh> meshes_;
};

#pragma once

#include "Animation.hpp"
#include "Bone.hpp"
#include "Mesh.hpp"
#include <filesystem>


class BoneTransform;

class Model
{
  public:
    bool import(const std::filesystem::path& path);

    void addBone(Bone&& bone);
    void addMesh(Mesh&& mesh);
    void addAnimation(Animation&& animation);

    size_t getBoneCount() const;
    size_t getBoneIndex(const std::string& name) const;
    const Bone& getBone(size_t index) const;
    Bone& getBone(size_t index);
    const std::vector<Mesh>& getMeshes() const;
    std::vector<std::string> getAnimationNames() const;
    size_t getAnimationIndex(const std::string& name) const;
    const Animation& getAnimation(size_t index) const;
    std::vector<mat4> getTransformMatrices(const BoneTransform& transform) const;
    float intersectRay(const vec3& ray_origin, const vec3& ray_direction, const BoneTransform& bone_transform) const;

    static const size_t	npos = static_cast<size_t>(-1);

  private:
    std::vector<Bone> bones_;
    std::unordered_map<std::string, size_t> bone_names_;
    std::vector<Mesh> meshes_;
    std::vector<Animation> animations_;
    std::unordered_map<std::string, size_t> animation_names_;
};

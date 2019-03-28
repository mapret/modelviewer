#include "BoneTransform.hpp"
#include "Model.hpp"
#include "ModelImporter.hpp"
#include "math/Intersections.hpp"
#include <cassert>


bool Model::import(const std::filesystem::path& path)
{
  return ModelImporter::import(path, *this);
}

void Model::addBone(Bone&& bone)
{
  bone_names_[bone.getName()] = bones_.size();
  bones_.push_back(std::move(bone));
}

void Model::addMesh(Mesh&& mesh)
{
  meshes_.push_back(std::move(mesh));
}

void Model::addAnimation(Animation&& animation)
{
  animation_names_[animation.name] = animations_.size();
  animations_.push_back(std::move(animation));
}

size_t Model::getBoneCount() const
{
  return bones_.size();
}

size_t Model::getBoneIndex(const std::string& name) const
{
  auto it = bone_names_.find(name);
  if (it == bone_names_.end())
    return npos;
  return it->second;
}

const Bone& Model::getBone(size_t index) const
{
  return bones_[index];
}

Bone& Model::getBone(size_t index)
{
  return bones_[index];
}

const std::vector<Mesh>& Model::getMeshes() const
{
  return meshes_;
}

std::vector<std::string> Model::getAnimationNames() const
{
  std::vector<std::string> names;
  names.reserve(animation_names_.size());
  for (const auto& animation : animation_names_)
    names.push_back(animation.first);
  return names;
}

size_t Model::getAnimationIndex(const std::string& name) const
{
  auto it = animation_names_.find(name);
  if (it == animation_names_.end())
    return npos;
  return it->second;
}

const Animation& Model::getAnimation(size_t index) const
{
  return animations_[index];
}

std::vector<mat4> Model::getTransformMatrices(const BoneTransform& transform) const
{
  std::vector<mat4> bone_data(getBoneCount());
  bool animation_active = transform.isAnimationActive();
  std::function<void(size_t, const mat4&)> setupBones = [&](size_t bone_index, const mat4& parent_transform)
  {
    const auto& bone = getBone(bone_index);
    mat4 self_transform = parent_transform * (animation_active ? transform.getTransform(bone_index) : bone.getNodeOffset());
    bone_data[bone_index] = self_transform * bone.getBoneOffset();
    for (const auto& child_index : bone.getChildIndices())
      setupBones(child_index, self_transform);
  };
  setupBones(0, mat4());
  return bone_data;
}

float Model::intersectRay(const vec3& ray_origin, const vec3& ray_direction, const BoneTransform& transform) const
{
  auto bone_transforms = getTransformMatrices(transform);
  float t = std::numeric_limits<float>::infinity();
  forEachTriangle(bone_transforms, [&](const vec3& p1, const vec3& p2, const vec3& p3)
  {
    t = std::min(t, Intersections::rayTriangle(p1, p2, p3, ray_origin, ray_direction));
  });
  return t;
}

void Model::forEachTriangle(const std::vector<mat4>& bone_transforms, Mesh::TriangleCallback callback) const
{
  for (const auto& mesh : meshes_)
    mesh.forEachTriangle(bone_transforms, callback);
}

#include "Model.hpp"
#include "ModelImporter.hpp"
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

#pragma once

#include <filesystem>


class Model;
struct aiAnimation;
struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

class ModelImporter
{
  public:
    static bool import(const std::filesystem::path& path, Model& model);

  private:
    ModelImporter() = default;
    bool importImpl(const std::filesystem::path& path, Model& model);
    void processNode(aiNode* node, size_t& index);
    void processMesh(aiMesh* ai_mesh, size_t bone_index);
    Material loadMaterial(aiMaterial* material);
    void processAnimation(aiAnimation* ai_animation);

    Model* model_;
    const aiScene* scene_;
    std::filesystem::path directory_;
    bool valid = true;
};

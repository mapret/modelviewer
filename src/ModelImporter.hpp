#pragma once

#include <filesystem>


class Model;
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

    Model* model_;
    std::unique_ptr<const aiScene> scene_;
    std::filesystem::path directory_;
    bool valid = true;
};

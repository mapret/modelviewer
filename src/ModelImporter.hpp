#pragma once

#include "Material.hpp"
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
    bool import(const std::filesystem::path& path, Model& model);
    static const std::string& getSupportedExtensions();
    const std::string& getErrorMessage() const;

  private:
    void processNode(aiNode* node, size_t& index);
    void processMesh(aiMesh* ai_mesh, size_t bone_index);
    Material loadMaterial(aiMaterial* material);
    void processAnimation(aiAnimation* ai_animation);

    Model* model_;
    const aiScene* scene_;
    std::filesystem::path directory_;
    std::string error_message_;
};

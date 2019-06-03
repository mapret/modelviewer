#include "Bone.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "ModelImporter.hpp"
#include "gl_tools/Error.hpp"
#include "gl_tools/GL.hpp"
#include "gl_tools/ImageIO.hpp"
#include "gl_tools/Texture.hpp"
#include <cassert>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>


bool ModelImporter::import(const std::filesystem::path& path, Model& model)
{
  model_ = &model;
  directory_ = path.parent_path();

  Assimp::Importer importer;
  scene_ = importer.ReadFile(path.string(), aiProcess_FlipUVs | aiProcessPreset_TargetRealtime_MaxQuality);
  if (!scene_ || scene_->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene_->mRootNode)
  {
    error_message_ = importer.GetErrorString();
    return false;
  }

  size_t index = 0;
  processNode(scene_->mRootNode, index);

  for (unsigned i = 0; i < scene_->mNumAnimations; i++)
    processAnimation(scene_->mAnimations[i]);

  return true;
}

const std::string& ModelImporter::getSupportedExtensions()
{
  static std::string extensions = []()
  {
    std::string tmp;
    Assimp::Importer importer;
    importer.GetExtensionList(tmp);
    return tmp;
  }();
  return extensions;
}

const std::string& ModelImporter::getErrorMessage() const
{
  return error_message_;
}

void ModelImporter::processNode(aiNode* node, size_t& index)
{
  Bone bone;
  bone.setName(std::string(node->mName.C_Str()));
  const aiMatrix4x4& m = node->mTransformation;
  bone.setNodeOffset(mat4(m.a1, m.b1, m.c1, m.d1,
                          m.a2, m.b2, m.c2, m.d2,
                          m.a3, m.b3, m.c3, m.d3,
                          m.a4, m.b4, m.c4, m.d4));
  model_->addBone(std::move(bone));

  for (unsigned i = 0; i < node->mNumMeshes; i++)
    processMesh(scene_->mMeshes[node->mMeshes[i]], index - 1);

  size_t current_index = index;
  for (unsigned i = 0; i < node->mNumChildren; i++)
  {
    index++;
    model_->getBone(current_index).addChildIndex(index);
    processNode(node->mChildren[i], index);
  }
}

void ModelImporter::processMesh(aiMesh* ai_mesh, size_t bone_index)
{
  std::vector<GeometryVertex> geometry_vertices;
  std::vector<GraphicsVertex> graphics_vertices;
  std::vector<uint32_t> indices;

  for(unsigned int i = 0; i < ai_mesh->mNumVertices; i++)
  {
    GeometryVertex geometry_vertex;
    GraphicsVertex graphics_vertex;
    geometry_vertex.position = vec3(ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y, ai_mesh->mVertices[i].z);
    graphics_vertex.normal = vec3(ai_mesh->mNormals[i].x, ai_mesh->mNormals[i].y, ai_mesh->mNormals[i].z);
    if(ai_mesh->mTextureCoords[0])
    {
      //Use only first occurring texture coordinate
      graphics_vertex.uv = vec2(ai_mesh->mTextureCoords[0][i].x, ai_mesh->mTextureCoords[0][i].y);
    }
    geometry_vertices.push_back(geometry_vertex);
    graphics_vertices.push_back(graphics_vertex);
  }

  std::vector<unsigned> num_bone_weights(geometry_vertices.size(), 0);
  for (unsigned int i = 0; i < ai_mesh->mNumBones; i++)
  {
    const aiBone* bone = ai_mesh->mBones[i];
    size_t _bone_index = model_->getBoneIndex(bone->mName.C_Str());
    const aiMatrix4x4& m = bone->mOffsetMatrix; //TODO: is mOffsetMatrix always the same for same _bone_index?
    //Could also premultiply vertices with bone_offset^-1 ??
    model_->getBone(_bone_index).setBoneOffset(mat4(m.a1, m.b1, m.c1, m.d1,
                                                    m.a2, m.b2, m.c2, m.d2,
                                                    m.a3, m.b3, m.c3, m.d3,
                                                    m.a4, m.b4, m.c4, m.d4));
    for (unsigned int j = 0; j < bone->mNumWeights; j++)
    {
      const aiVertexWeight& weight = bone->mWeights[j];
      uint32_t& num = num_bone_weights[weight.mVertexId];
      assert(num < 4);
      geometry_vertices[weight.mVertexId].bone_indices[num] = (uint32_t)_bone_index;
      geometry_vertices[weight.mVertexId].vertex_weights[num] = weight.mWeight;
      num++;
    }
  }
  for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++)
  {
    const auto& face = ai_mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }

  for (unsigned i = 0; i < geometry_vertices.size(); i++)
    if (num_bone_weights[i] == 0)
    {
      geometry_vertices[i].bone_indices.x = (uint32_t)bone_index;
      geometry_vertices[i].vertex_weights.x = 1.f;
    }

  aiMaterial* ai_material = scene_->mMaterials[ai_mesh->mMaterialIndex];
  Material material = loadMaterial(ai_material);

  Mesh mesh(std::move(geometry_vertices), graphics_vertices, std::move(indices));
  mesh.setMaterial(std::move(material));
  model_->addMesh(std::move(mesh));
}

Material ModelImporter::loadMaterial(aiMaterial* mat)
{
  Material material;
  for (const auto& texture_type : { //TODO: Also support specular/normal textures
      aiTextureType_DIFFUSE
  })
  {
    for (unsigned int i = 0; i < mat->GetTextureCount(texture_type); i++)
    {
      aiString relative_texture_path;
      mat->GetTexture(texture_type, i, &relative_texture_path);
      bool skip = false;
      std::replace(relative_texture_path.data, relative_texture_path.data + relative_texture_path.length, '\\', '/');
      std::filesystem::path path_to_file = directory_ / relative_texture_path.C_Str();
      vec2u size;
      material.texture = GL::loadImage(path_to_file, size);
    }
  }

  aiColor3D c;
  if (mat->Get("$clr.diffuse", 0, 0, c) == aiReturn_SUCCESS)
    material.color_diffuse = vec3(c.r, c.g, c.b);
  if (mat->Get("$clr.specular", 0, 0, c) == aiReturn_SUCCESS)
    material.color_specular = vec3(c.r, c.g, c.b);

  return material;
}

void ModelImporter::processAnimation(aiAnimation* ai_animation)
{
  float scale = 1.f / static_cast<float>(ai_animation->mTicksPerSecond);
  Animation animation;
  animation.name = ai_animation->mName.C_Str();
  animation.duration = static_cast<float>(ai_animation->mDuration - 1) * scale; // -1 for smooth looping

  // A channel contains all animation information about a single bone
  for (unsigned i = 0; i < ai_animation->mNumChannels; i++)
  {
    auto* channel = ai_animation->mChannels[i];
    size_t bone_index = model_->getBoneIndex(channel->mNodeName.C_Str());
    assert(bone_index != static_cast<size_t>(-1));
    Animation::Keyframes keyframes;
    for (unsigned j = 0; j < channel->mNumPositionKeys; j++)
    {
      const auto& key = channel->mPositionKeys[j];
      keyframes.position_keyframes[static_cast<float>(key.mTime) * scale] = vec3(key.mValue.x, key.mValue.y, key.mValue.z);
    }
    for (unsigned j = 0; j < channel->mNumScalingKeys; j++)
    {
      const auto& key = channel->mScalingKeys[j];
      keyframes.scale_keyframes[static_cast<float>(key.mTime) * scale] = vec3(key.mValue.x, key.mValue.y, key.mValue.z);
    }
    for (unsigned j = 0; j < channel->mNumRotationKeys; j++)
    {
      const auto& key = channel->mRotationKeys[j];
      keyframes.rotation_keyframes[static_cast<float>(key.mTime) * scale] = quat(key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w);
    }
    animation.keyframes[bone_index] = keyframes;
  }

  model_->addAnimation(std::move(animation));
}

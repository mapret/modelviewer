#include "Camera.hpp"
#include "Model.hpp"
#include "Renderer.hpp"
#include "gl_tools/GL.hpp"
#include "plaintext/opengl_shader.gen.hpp"


Renderer::Renderer()
{
  glEnable(GL_DEPTH_TEST);
  shader_ = GL::Program("default", plaintext::phong_vs, plaintext::phong_fs);
}

void Renderer::draw(const Model& model, const Camera& camera)
{
  if (model.getBoneCount() == 0)
    return;

  shader_.use();
  shader_.setMat4("model", mat4());
  shader_.setMat4("proj_view", camera.getProjectionMatrix() * camera.getViewMatrix());

  std::vector<mat4> bone_data(model.getBoneCount());
  std::function<void(size_t, const mat4&)> setupBones = [&](size_t bone_index, const mat4& parent_transform)
  {
    const auto& bone = model.getBone(bone_index);
    mat4 self_transform = parent_transform * bone.getNodeOffset();
    bone_data[bone_index] = self_transform * bone.getBoneOffset();
    for (const auto& child_index : bone.getChildIndices())
      setupBones(child_index, self_transform);
  };
  setupBones(0, mat4());
  shader_.setMat4("bones", bone_data.data(), bone_data.size());

  for (const auto& mesh : model.getMeshes())
  {
    const Material& material = mesh.getMaterial();
    shader_.setVec3("uColorDiffuse", material.color_diffuse);
    material.texture.bind(GL_TEXTURE0);
    mesh.getVertexArray().bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.getNumberOfIndices()), GL_UNSIGNED_INT, nullptr);
  }
  GL::VertexArray::unbind();
}

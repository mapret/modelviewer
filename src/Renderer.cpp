#include "BoneTransform.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Renderer.hpp"
#include "gl_tools/Error.hpp"
#include "gl_tools/GL.hpp"
#include "plaintext/opengl_shader.gen.hpp"


namespace
{
  template<typename T, class Container>
  T interpolate(const Container& data, float time)
  {
    if (time <= 0)
      return data.begin()->second;
    else if (time >= (--data.end())->first)
      return (--data.end())->second;
    auto p2 = data.lower_bound(time);
    auto p1 = std::prev(p2);
    if constexpr(std::is_same<T, quat>::value)
      return  quat::mix(p1->second, p2->second, (time - p1->first) / (p2->first - p1->first));
    else
      return math::mapRange(time, p1->first, p2->first, p1->second, p2->second);
  }
}

Renderer::Renderer()
{
  glEnable(GL_DEPTH_TEST);
  shader_ = GL::Program("default", plaintext::phong_vs, plaintext::phong_fs);
}

void Renderer::update(const Model& model, BoneTransform& transform, float dt)
{
  size_t animation_index = transform.getCurrentAnimationIndex();
  if (animation_index == BoneTransform::npos) // No currently active animation
    return;

  const auto& animation = model.getAnimation(animation_index);
  float& animation_time = transform.getAnimationTime();
  for (const auto& bone : animation.keyframes)
  {
    auto position = interpolate<vec3>(bone.second.position_keyframes, animation_time);
    auto scale = interpolate<vec3>(bone.second.scale_keyframes, animation_time);
    auto rotation = interpolate<quat>(bone.second.rotation_keyframes, animation_time);
    transform.setTransform(bone.first, mat4().translate(position).scale(scale) * rotation.toMat4());
  }
  animation_time = std::fmod(animation_time + dt, animation.duration);
}

void Renderer::draw(const Model& model, const BoneTransform& transform, const Camera& camera)
{
  if (model.getBoneCount() == 0)
    return;

  shader_.use();
  shader_.setMat4("model", mat4());
  shader_.setMat4("proj_view", camera.getProjectionMatrix() * camera.getViewMatrix());
  shader_.setVec3("uLightDirection", camera.getViewDirection());

  auto bone_data = model.getTransformMatrices(transform);
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
  GL::checkError("Renderer::draw()");
}

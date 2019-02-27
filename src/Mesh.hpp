#pragma once

#include "noncopyable.hpp"
#include "Material.hpp"
#include "Vertex.hpp"
#include "gl_tools/VertexArray.hpp"
#include "gl_tools/Buffer.hpp"
#include <cstdint>
#include <vector>


class Mesh
{
  public:
    Mesh(std::vector<GeometryVertex>&& geometry_vertices,
         const std::vector<GraphicsVertex>& graphics_vertices,
         std::vector<uint32_t>&& indices);
    Mesh(Mesh&& other) = default;
    ~Mesh();

    void setMaterial(Material&& material);
    const Material& getMaterial() const;
    const GL::VertexArray& getVertexArray() const;
    size_t getNumberOfIndices() const;

  private:
    std::vector<GeometryVertex> vertices_;
    std::vector<uint32_t> indices_;

    Material material_;
    GL::VertexArray vao_;
    GL::Buffer vbo_, ebo_;
};

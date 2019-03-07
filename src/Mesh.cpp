#include "Mesh.hpp"
#include "gl_tools/Error.hpp"
#include "gl_tools/GL.hpp"


Mesh::Mesh(std::vector<GeometryVertex>&& geometry_vertices,
           const std::vector<GraphicsVertex>& graphics_vertices,
           std::vector<uint32_t>&& indices)
  : vertices_(std::move(geometry_vertices)),
    indices_(std::move(indices))
{
  size_t graphics_offset = vertices_.size() * sizeof(GeometryVertex);
  size_t buffer_size = graphics_offset + graphics_vertices.size() * sizeof(GraphicsVertex);

  vao_.bind();

  vbo_.bind(GL_ARRAY_BUFFER);
  glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(buffer_size), nullptr, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(vertices_.size() * sizeof(GeometryVertex)), vertices_.data());
  glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr> (graphics_offset), static_cast<GLsizeiptr>(graphics_vertices.size() * sizeof(GraphicsVertex)), graphics_vertices.data());

  ebo_.bind(GL_ELEMENT_ARRAY_BUFFER);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(uint32_t) * indices_.size()), indices_.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0); //Vertex positions
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GeometryVertex), (void*)offsetof(GeometryVertex, position));
  glEnableVertexAttribArray(1); //Vertex normals
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GraphicsVertex), (void*)(graphics_offset + offsetof(GraphicsVertex, normal)));
  glEnableVertexAttribArray(2); //Vertex uvs
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GraphicsVertex), (void*)(graphics_offset + offsetof(GraphicsVertex, uv)));
  glEnableVertexAttribArray(3); //Bone indices
  glVertexAttribIPointer(3, 4, GL_UNSIGNED_INT, sizeof(GeometryVertex), (void*)offsetof(GeometryVertex, bone_indices));
  glEnableVertexAttribArray(4); //Bone weights
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(GeometryVertex), (void*)offsetof(GeometryVertex, vertex_weights));

  GL::VertexArray::unbind();
  GL::checkError("Mesh::Mesh()");
}

Mesh::~Mesh()
{
  GL::checkError("Mesh::~Mesh()");
}

void Mesh::setMaterial(Material&& material)
{
  material_ = std::move(material);
}

const Material& Mesh::getMaterial() const
{
  return material_;
}

const GL::VertexArray& Mesh::getVertexArray() const
{
  return vao_;
}

size_t Mesh::getNumberOfIndices() const
{
  return indices_.size();
}

uniform mat4 model;
uniform mat4 proj_view;
uniform mat4 bones[1022];
//TODO: Assume 1024 mat4 are allowed
//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGet.xhtml
//Theoretical minimum is GL_MAX_VERTEX_UNIFORM_COMPONENTS (=1024) / 16 = 64

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUv;
layout (location = 3) in uvec4 aBoneIndices;
layout (location = 4) in vec4 aBoneWeights;

out vec4 Position;
out vec3 Normal;
out vec2 Uv;

void main()
{
   Position = proj_view * (
       bones[aBoneIndices.x] * vec4(aPos, 1.0f) * aBoneWeights.x +
       bones[aBoneIndices.y] * vec4(aPos, 1.0f) * aBoneWeights.y +
       bones[aBoneIndices.z] * vec4(aPos, 1.0f) * aBoneWeights.z +
       bones[aBoneIndices.w] * vec4(aPos, 1.0f) * aBoneWeights.w);
   gl_Position = Position;
   Normal = mat3(model) *
       mat3(bones[aBoneIndices.x]) * aNormal * aBoneWeights.x +
       mat3(bones[aBoneIndices.y]) * aNormal * aBoneWeights.y +
       mat3(bones[aBoneIndices.z]) * aNormal * aBoneWeights.z +
       mat3(bones[aBoneIndices.w]) * aNormal * aBoneWeights.w;
   Uv = aUv;
}

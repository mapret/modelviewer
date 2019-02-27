layout (location = 0) out vec4 FragColor;

in vec4 Position;
in vec3 Normal;
in vec2 Uv;

layout (binding = 0) uniform sampler2D TextureSampler;
uniform vec3 uColorDiffuse;
uniform vec3 uColorSpecular;

void main()
{
  vec3 n = normalize(Normal);
  vec3 light_direction = normalize(vec3(1, -1, 1));
  vec3 ambient = vec3(0.1, 0.1, 0.1);
  float lambert = max(dot(n, -light_direction), 0);
  FragColor = vec4(texture(TextureSampler, Uv).xyz * uColorDiffuse * lambert + ambient, 1.f);
}

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

float height(vec2 point) {
    return point.y;
}

void main()
{
    vec3 off = vec3(1, 1, 1);
    float hL = height(aPos.xy - off.xz);
    float hR = height(aPos.xy + off.xz);
    float hD = height(aPos.xy - off.zy);
    float hU = height(aPos.xy + off.zy);

    vec3 normal = vec3(
        hL - hR,
        hD - hU,
        2.0
    );

    normal = normalize(normal);

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));

    TexCoord = aTexCoord;
    Normal = normal;
}
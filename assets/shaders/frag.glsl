#version 330 core

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

in vec2 oTexCoords;
out vec4 fragColor;

void main() {
    fragColor = vec4(1, 1, 1, 1);
}

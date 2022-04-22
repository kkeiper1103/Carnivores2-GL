#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

//
vec3 lightPos = vec3(0, 50.0, 50); // eventually, this will become a uniform
vec3 lightColor = vec3(1.0, 1.0, 1.0);

void main()
{
    // ambient
    float ambientStrength = 0.8;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = Normal;
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) *  texture(texture1, TexCoord).xyz;

    FragColor = vec4(result, 1.0);
}
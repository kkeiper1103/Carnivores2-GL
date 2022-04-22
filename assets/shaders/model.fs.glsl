#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // this could imaginably be an easy way to set lighting calculations during time of day
    // .2 for night, .6 for dawn, 1.0 for day
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

    // linearly interpolate between both textures (80% container, 20% awesomeface)
    vec4 texColor = texture(texture1, TexCoord);

    if(texColor.a < .15)
        discard;

    FragColor = texColor;
}
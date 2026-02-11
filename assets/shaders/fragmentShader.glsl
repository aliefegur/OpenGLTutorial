#version 330 core

out vec4 FragColor;

in vec3 vColor;
in vec2 vTexCoord;

uniform vec3 uColor;

uniform sampler2D myTexture;

void main()
{
    //FragColor = vec4(vColor * uColor, 1.0f);
    FragColor = texture(myTexture, vTexCoord);
}

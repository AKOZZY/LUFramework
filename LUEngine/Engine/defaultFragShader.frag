#version 330 core
out vec4 FragColor;
  
in vec2 textureCoord;

uniform sampler2D textureImage;

void main()
{
    FragColor = texture(textureImage, textureCoord);
} 
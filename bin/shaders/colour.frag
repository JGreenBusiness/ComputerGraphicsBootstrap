//  Asimple flat-colour shader
#version 410

out vec4 FragColour;

uniform vec4 BaseColour;

void main()
{
    FragColour = BaseColour;
}
//  Asimple flat-colour shader
#version 410

in vec2 vTexCoord;
uniform sampler2D colourTarget;

out vec4 FragColour;

vec4 Default(vec2 texCoord)
{
    return texture(colourTarget,texCoord);
}

void main()
{
    // This will calculate the exel size
    vec2 texSize = textureSize(colourTarget,0);
    vec2 texelSize = 1.0f / texSize;

    // Then we will adjust the coordinate
    vec2 scale = (texSize - texelSize) / texSize;
    vec2 texCoord = vTexCoord / scale + texelSize * 0.5f;

    // Output post process effect here
    FragColour = Default(texCoord);
}
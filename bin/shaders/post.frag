//  Asimple flat-colour shader
#version 410

in vec2 vTexCoord;
uniform sampler2D colourTarget;
uniform int postProcessTarget;
uniform int windowWidth;
uniform int windowHeight;
uniform float time;

out vec4 FragColour;

vec4 Default(vec2 texCoord)
{
    return texture(colourTarget,texCoord);
}

vec4 BoxBlur(vec2 texCoord)
{
    vec2 texel = 1.0f / textureSize(colourTarget, 0);

    vec4 colour = texture(colourTarget, texCoord);
    colour += texture(colourTarget, texCoord + texel * vec2(-1, 1));
    colour += texture(colourTarget, texCoord + texel * vec2(-1, 0));
    colour += texture(colourTarget, texCoord + texel * vec2(-1, -1));
    colour += texture(colourTarget, texCoord + texel * vec2(0, 1));
    colour += texture(colourTarget, texCoord + texel * vec2(0, -1));
    colour += texture(colourTarget, texCoord + texel * vec2(1, 1));
    colour += texture(colourTarget, texCoord + texel * vec2(1, 0)); 
    colour += texture(colourTarget, texCoord + texel * vec2(1, -1)); 

    return colour / 9; 
}

vec4 Distort(vec2 texCoord)
{ 
    vec2 mid = vec2(0.5f); 
    float distanceFromTheCenter = distance(texCoord, mid); 
    vec2 normalizeCoord = normalize(texCoord - mid); 
    float bias = distanceFromTheCenter + sin(distanceFromTheCenter * 15) * 0.05f; 
    vec2 newCoord = mid + bias * normalizeCoord; 

    return texture(colourTarget, newCoord); 
}

vec4 EdgeDetection(vec2 texCoord)
{
    float w = 1.0f / windowWidth;
    float h = 1.0f / windowHeight;

    vec4 k[9];
    k[0] = texture(colourTarget, texCoord + vec2(-w, -h));
    k[1] = texture(colourTarget, texCoord + vec2(0, -h));
    k[2] = texture(colourTarget, texCoord + vec2(w, -h));
    k[3] = texture(colourTarget, texCoord + vec2(-w,0));
    k[4] = texture(colourTarget, texCoord);
    k[5] = texture(colourTarget, texCoord + vec2(w, 0));
    k[6] = texture(colourTarget, texCoord + vec2(-w, h));
    k[7] = texture(colourTarget, texCoord + vec2(0, h));
    k[8] = texture(colourTarget, texCoord + vec2(h,w));

    vec4 sobelEdgeH = k[2] + (2.0f * k[5]) + k[8] - (k[0] + (2.0f * k[3]) + k[6]);
    vec4 sobelEdgeV = k[0] + (2.0f * k[1]) + k[2] - (k[6] + (2.0f * k[7]) + k[8]);

    vec4 sobel = sqrt((sobelEdgeH * sobelEdgeH) + (sobelEdgeV * sobelEdgeV));

    return vec4(1.0f - sobel.rgb, 1.0f);

}

vec4 Sepia(vec2 texCoord)
{

    vec4 texColour = texture(colourTarget,texCoord);

    float rr = .3;
    float rg = .769;
    float rb = .189;
    float ra = 0.0;
    
    float gr = .3;
    float gg = .686;
    float gb = .168;
    float ga = 0.0;
    
    float br = .272;
    float bg = .534;
    float bb = .131;
    float ba = 0.0;
    
    float red = (rr * texColour.r) + (rb * texColour.b) + (rg * texColour.g) + (ra * texColour.a);
    float green = (gr * texColour.r) + (gb * texColour.b) + (gg * texColour.g) + (ga * texColour.a);
    float blue = (br * texColour.r) + (bb * texColour.b) + (bg * texColour.g) + (ba * texColour.a);

    return vec4(red,green,blue,1.0);
}

vec4 GreyScale(vec2 texCoord)
{
    vec4 texColour = texture(colourTarget,texCoord);

    float gs = texColour.r*0.3+texColour.g*0.6+texColour.b*0.1;

    return vec4(gs, gs, gs, 1.0); 
}

vec4 Inverted(vec2 texCoord)
{
    vec4 texColour = texture(colourTarget,texCoord);

    return vec4(1 - texColour.r , 1 - texColour.g ,1 -  texColour.b, 1.0); 
}

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

vec4 Scanlines(vec2 texCoord)
{
    float density = 30;
    float opacityScanline = .3;
    float opacityNoise = .2;
    float flickering = 0.003;

    vec4 texColour = texture(colourTarget,texCoord);
    
    float count = windowHeight * density;

    float scaledY = texCoord.y + time * .3f;

    vec2 sl = vec2(sin(scaledY * count), cos(scaledY * count));
	vec3 scanlines = vec3(sl.x, sl.y, sl.x);

    texColour.rgb += texColour.rgb * (scanlines * opacityScanline);
    texColour.rgb += texColour.rgb * vec3(random(texCoord * time)) * opacityNoise;
    texColour.rgb += texColour.rgb * sin(110.0 * time) * flickering;

    return vec4(texColour);
}


void main()
{
    // This will calculate the exel size
    vec2 texSize = textureSize(colourTarget,0);
    vec2 texelSize = 1.0f / texSize;

    // Then we will adjust the coordinate
    vec2 scale = (texSize - texelSize) / texSize;
    vec2 texCoord = vTexCoord / scale + texelSize * 0.5f;

    switch(postProcessTarget)
     { 
        default: // Default 
        { 
            // Output post process effect here FragColor = Default(texCoord);
            FragColour = Default(texCoord);
        } 
        case -1: // BoxBlur
        { 
            FragColour = Default(texCoord);
            break;
        } 
        case 0: // BoxBlur
        { 
            FragColour = BoxBlur(texCoord);
            break;
        } 
        case 1: // Distort 
        { 
            FragColour = Distort(texCoord);
            break;
        } 
        case 2: // Edge Detection
        { 
            FragColour = EdgeDetection(texCoord);
            break;
        } 
        case 3: // Sepia
        {
            FragColour = Sepia(texCoord);
            break;
        } 
        case 4: // Scanlines
        { 
            FragColour = Scanlines(texCoord);
            break;
        } 
        case 5: // Grey Scale
        { 
            FragColour = GreyScale(texCoord);
             break;
        } 
        case 6: // Invert
        { 
            FragColour = Inverted(texCoord);
            break;
        } 
        case 7: // Pixelizer
        { 
            FragColour = Default(texCoord);
            break;
        } case 8: // Posterization
        { 
            FragColour = Default(texCoord);
            break;
        } case 9: // Distance Fog
        { 
            FragColour = Default(texCoord);
            break;
        } case 10: // Depth of Field
        { 
            FragColour = Default(texCoord);
            break;
        }
     }
}
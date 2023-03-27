//  A Phong shader
#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;


out vec4 FragColour;

// Camera Data
uniform vec3 CameraPosition;


// Texture Data
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

const int MAX_LIGHTS = 4;
uniform int numLights;
uniform vec3 PointLightColours[MAX_LIGHTS];
uniform vec3 PointlightPositions[MAX_LIGHTS];

// Model Data
uniform vec3 Ka;  // The ambient material colour
uniform vec3 Kd;  // The diffuse material colour
uniform vec3 Ks;  // The specular material colour
uniform float Ns; // The Specular power of Ks

// Light Data
uniform vec3 AmbientColour;
uniform vec3 LightColour;
uniform vec3 LightDirection;

vec3 Diffuse(vec3 direction, vec3 colour, vec3 normal)
{
    return colour * max(0, dot(normal, -direction));
}

vec3 Specular(vec3 direction, vec3 colour, vec3 normal, vec3 view)
{
    vec3 R = reflect(direction,normal);
    
    float specularTerm = pow(max(0, dot(R, view)), Ns);

    return specularTerm * colour;
}

void main()
{
    // Set the normal and the light direction
    vec3 N = normalize(vNormal);
    vec3 T = normalize(vTangent);
    vec3 B = normalize(vBiTangent);
    vec3 L = normalize(LightDirection);

    mat3 TBN = mat3(T,B,N);

    vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
    vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
    vec3 texNormal = texture(normalTexture, vTexCoord).rgb;

    N = normalize(TBN * (texNormal * 2 - 1));

    // Calculate the negative light drection (Lambert Term)
    float lambertTerm = max(0,min(1,dot(N,-L)));

    // Calclate the view vector...
    vec3 V = normalize(CameraPosition - vPosition.xyz);
    //... and the reflection vector
    vec3 R = reflect(L,N);

    // calculate the diffuse value of light from the global source
    vec3 diffuseTotal = Diffuse(L, LightColour, N);

    // Calculate the specular view of light from the global source
    vec3 specularTotal = Specular(L, LightColour, N, V);

    for (int i = 0; i < numLights; i++)
    {
        vec3 direction = vPosition.xyz - PointlightPositions[i];
        float distance = length(direction);
        direction = direction / distance;

        // Set the Lighting intensity with the inverse square law
        vec3 colour = PointLightColours[i] / (distance*distance);
        diffuseTotal += Diffuse(direction, colour,N);
        specularTotal += Specular(direction, colour, N, V);
    }

    // Calculate the properties of each colour type
    vec3 ambient = AmbientColour * Ka * texDiffuse;
    vec3 diffuse =  diffuseTotal * Kd * texDiffuse;
    vec3 specular = specularTotal * Ks * texSpecular;


    FragColour = vec4(ambient + diffuse + specular,1);
}
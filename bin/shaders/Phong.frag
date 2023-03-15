//  A Phong shader
#version 410

out vec4 vPosition;
in vec3 vNormal;

out vec4 FragColour;

uniform vec3 CameraPosition;

// Model Data
uniform vec3 Ka; // The ambient material colour
uniform vec3 Kd; // The diffuse material colour
uniform vec3 Ks; // The specular material colour
uniform float Ns; // The Specular power of Ks

// Light Data
uniform vec3 AmbientColour;
uniform vec3 LightColour;
uniform vec3 LightDirection;

void main()
{
    // Set the normal and the light direction
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDirection);

    // Calculate the negative light drection (Lambert Term)
    float lambertTerm = max(0,min(1,dot(N,-L)));

    // Calclate the view vector...
    vec3 V = normalize(CameraPosition - vPosition.xyz);
    //... and the reflection vector
    vec3 R = reflect(L,N);

    // Calculate the specular term
    float specularTerm = pow(max(0,dot(R,V)),Ns);

    // Calculate the properties of each colour type
    vec3 ambient = AmbientColour * Ka;
    vec3 diffuse = LightColour * Kd * lambertTerm;
    vec3 specular = LightColour * Ks *specularTerm;

    FragColour = vec4(ambient + diffuse + specular,1);
}
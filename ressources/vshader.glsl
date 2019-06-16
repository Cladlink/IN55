#version 330
in vec4 position;
in vec3 color;
in vec3 normal;

out vec3 normalWorld;
out vec3 vertexPositionWorld;
out vec3 vertexToFragmentColor;
out vec4 fColor;
out vec3 V;
flat out int fIsColor;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldMatrix;
uniform mat4 worldToViewMatrix;
uniform float time;
uniform vec4 translation;
uniform vec3 axis;
uniform float angle;
uniform vec4 homothetie;
uniform int isColor;

mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

float random (vec2 st) {
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
}

//! [0]
void main()
{
    // Nécessaire pour la construction des formes (ballon de plage, damier, etc.) dans le fragment shader
    V = vec3(position);
    // Calcul des transformations géométriques
    vec4 pos = position + translation;
    vec4 temp = pos;
    pos = pos - translation;
    pos = pos * rotationMatrix(axis,angle);
    pos = pos + translation;
    pos = pos * homothetie;
    // Calcul de la matrice MVP
    gl_Position = modelToProjectionMatrix * pos;
    // Normalisation de la matrice MVP
    normalWorld = vec3(modelToWorldMatrix * vec4(normal, 0));
    vertexPositionWorld = vec3(modelToWorldMatrix * pos);
    // Permet de modifier le rendu de la couleur en fonction des choix de l'utilisateur
    fIsColor = isColor;
    if (fIsColor == 0) {
        // Couleur classique
        fColor = vec4(color,1.0);
    } else if (fIsColor == 1) {
        // Couleur aléatoire en fonction du temps et de la position
        fColor = vec4(random((time)*gl_Position.xy),random((time+1.)*gl_Position.yz),random((time+1.)*gl_Position.zy),1.0);
    } else if (fIsColor == 2) {
        // Couleur en fonction des normales
        fColor = normalize(worldToViewMatrix * (vec4(normal,1.0)/2.0)+0.5);
    }
}




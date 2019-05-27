#version 330
layout(location = 1) in vec2 vertexUV;
uniform mat4 mvp;
uniform vec4 homotethie;
uniform float time;
uniform int isColor;
uniform mat4 normal;
uniform vec4 translation;

in vec3 position;
in vec3 color;

out vec4 fColor;
out vec4 fPosition;
out vec2 UV;
out float norme;
out vec4 vecNormal;
flat out int fIsColor;
out float fTime;

float random (vec2 st) {
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
}

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp * vec4(position, 1.0);
    gl_Position *= homotethie;
    gl_Position += translation;

    fPosition = gl_Position;
    UV = vertexUV;
    fIsColor = isColor;
    fTime = time;
    norme = sqrt(pow(gl_Position.x,2)+pow(gl_Position.y,2)+pow(gl_Position.z,2));
    vecNormal = gl_Position / norme;
    if (fIsColor == 1) {
        fColor = vec4(color,1.0);
    } else if (fIsColor == 2) {
        fColor = vec4(random((fTime)*fPosition.xy),random((fTime+1.)*fPosition.yz),random((fTime+1.)*fPosition.zy),1.0);
    } else if (fIsColor == 4) {
        fColor = normalize(normal * vecNormal);
    }
}
//! [0]

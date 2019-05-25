#version 330
layout(location = 1) in vec2 vertexUV;
uniform mat4 mvp;
uniform vec4 homotethie;
uniform float time;
uniform int isColor;

in vec3 position;
in vec3 color;

out vec3 fColor;
out vec4 fPosition;
out vec2 UV;
flat out int fIsColor;
out float fTime;

float random (vec2 st) {
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
}

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp * vec4( position, 1.0);
    gl_Position *= homotethie;
    fPosition = gl_Position;
    UV = vertexUV;
    fIsColor = isColor;
    fTime = time;
    if (fIsColor == 1) {
        fColor = color;
    } else if (fIsColor == 2) {
        fColor = vec3(random((fTime)*fPosition.xy),random((fTime+1.)*fPosition.yz),random((fTime+1.)*fPosition.zy));
    }
}
//! [0]

#version 330
layout(location = 1) in vec2 vertexUV;
uniform mat4 mvp;
uniform vec4 homotethie;
uniform float time;

in vec3 position;
in vec3 color;

out vec3 fColor;
out vec4 fPosition;
out vec2 UV;

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
    fColor = color;
    //fColor = vec3(random((time)*gl_Position.xy),random((time+1.)*gl_Position.yz),random((time+1.)*gl_Position.zy));
}
//! [0]

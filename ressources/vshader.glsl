#version 330
/*layout(location=0) vec4 vertexPositionModel;
layout(location=1) vec3 vertexColor;
layout(location=2) vec3 normalModel;
layout(location = 1) in vec2 vertexUV;
uniform mat4 mvp;

uniform float time;
uniform int isColor;
//uniform vec3 normal;


in vec3 position;
in vec3 color;

out vec4 fColor;
out vec4 fPosition;
out vec2 UV;
out vec3 n;
out float norme;
out vec4 vecNormal;
flat out int fIsColor;
out float fTime;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldMatrix;

out vec3 normalWorld;
out vec3 vertexPositionWorld;*/

in vec4 position;
in vec3 color;
in vec3 normal;


uniform vec4 homotethie;

out vec3 normalWorld;
out vec3 vertexPositionWorld;
out vec3 vertexToFragmentColor;
out vec4 fColor;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldMatrix;
uniform vec4 translation;

//! [0]
void main()
{
    vec4 pos = position + translation;
    gl_Position = modelToProjectionMatrix * pos;
    normalWorld = vec3(modelToWorldMatrix * vec4(normal, 0));
    vertexPositionWorld = vec3(modelToWorldMatrix * position);
    vertexToFragmentColor = color;
    fColor = vec4(color,1.0);
    // Calculate vertex position in screen space
    /*vec4 pos = vec4(position,1.) + translation;
    pos = pos * homotethie;
    gl_Position = mvp * pos;

    fPosition = gl_Position;
    UV = vertexUV;
    //n = normal;
    fIsColor = isColor;
    fTime = time;
    norme = sqrt(pow(gl_Position.x,2)+pow(gl_Position.y,2)+pow(gl_Position.z,2));
    vecNormal = gl_Position / norme;
    if (fIsColor == 1) {
        fColor = vec4(color,1.0);
    } else if (fIsColor == 2) {
        fColor = vec4(random((fTime)*fPosition.xy),random((fTime+1.)*fPosition.yz),random((fTime+1.)*fPosition.zy),1.0);
    } else if (fIsColor == 4) {
        //fColor = normalize(normal * vecNormal);
    }*/
}



float random (vec2 st) {
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
}
//! [0]

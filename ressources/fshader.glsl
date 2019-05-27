#version 330

flat in int fIsColor;
in vec4 fColor;
in vec2 UV;
in float fTime;
in vec4 fPosition;
in vec4 fNormal;

out vec4 fragColor;

uniform sampler2D image;

float random (vec2 st) {
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
}

void main()
{

    if (fIsColor == 0) {
        fragColor = vec4(texture2D(image, UV).rgb,1.0);
    } else if (fIsColor == 1 || fIsColor == 2 || fIsColor == 4) {
        fragColor = vec4(fColor);
    } else if (fIsColor == 3) {
        fragColor = vec4(random((fTime)*fPosition.xy),random((fTime+1.)*fPosition.yz),random((fTime+1.)*fPosition.zy),1.0);
    }
}

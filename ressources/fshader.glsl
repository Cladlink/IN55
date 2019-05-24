#version 330

flat in int fIsColor;
in vec3 fColor;
in vec2 UV;

out vec4 fragColor;

uniform sampler2D image;

void main()
{
    //fragColor = vec4(fColor, 1.0);
    //fragColor = vec4(1.0f,0.f,0.f,1.0);
    if (fIsColor == 1) {
        fragColor = vec4(fColor, 1.0);
    } else {
        fragColor = vec4(texture2D(image, UV).rgb,1.0);
    }
}

#version 330

in vec3 fColor;
in vec2 UV;

out vec4 fragColor;

uniform sampler2D image;

void main()
{
    //fragColor = vec4( fColor, 1.0 );
    fragColor = vec4(texture2D(image, UV).rgb,1.0);
}

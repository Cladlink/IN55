#version 330
/*
flat in int fIsColor;
in vec4 fColor;
in vec2 UV;
in float fTime;
in vec4 fPosition;
in vec4 fNormal;
in vec3 n;

out vec4 fragColor;

uniform sampler2D image;
uniform sampler2D mur;
uniform sampler2D nintendo;

out vec4 daColor;
in vec3 normalWorld;
in vec3 vertexPositionWorld;

uniform vec3 lightPositionWorld;
uniform vec3 eyePositionWorld;
uniform vec4 ambientLight;
uniform vec3 vertexToFragmentColor;*/

out vec4 daColor;
in vec3 normalWorld;
in vec3 vertexPositionWorld;

uniform vec3 lightPositionWorld;
uniform vec3 eyePositionWorld;
uniform vec4 ambientLight;
uniform vec3 vertexToFragmentColor;

float random (vec2 st) {
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
}

void main()
{
    /*vec3 eyeSpaceLigthDirection = vec3(0.0,0.0,1.0);
    float diffuse = max(0.0,dot(normalize(n),eyeSpaceLigthDirection));

    float a = smoothstep(-1.,-0.8,fPosition.y) * (1.0 - smoothstep(-0.6,-0.4,fPosition.y));
    float b = smoothstep(-0.6,-0.4,fPosition.y) * (1.0 - smoothstep(-0.1,0.2,fPosition.y));
    float c = smoothstep(-0.1,0.2,fPosition.y) * (1.0 - smoothstep(0.2,0.5,fPosition.y));
    float d = smoothstep(0.2,0.5,fPosition.y) * (1.0 - smoothstep(0.5,1.,fPosition.y));

    gl_FragColor = a*vec4(texture2D(mur,UV).xyz*diffuse,1.0)
    + b*vec4(texture2D(nintendo,UV).xyz*diffuse,1.0)
    + c*vec4(texture2D(mur,UV).xyz*diffuse,1.0)
    + d*vec4(texture2D(nintendo,UV).xyz*diffuse,1.0);
    */

    // Diffuse
    vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
    float brightness = dot(lightVectorWorld, normalize(normalWorld));
    vec4 diffuseLight = vec4(brightness, brightness, brightness, 1.0);

    // Specular
    vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
    vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
    float s = clamp(dot(reflectedLightVectorWorld, eyeVectorWorld), 0, 1);
    s = pow(s, 20);
    vec4 specularLight = vec4(s, 0, 0, 1);

    daColor = vec4(1.,1.,1.,1.);//ambientLight + clamp(diffuseLight, 0, 1) + specularLight;
    //vec4(vertexToFragmentColor, 1) +
    /*if (fIsColor == 0) {
        fragColor = vec4(texture2D(image, UV).rgb,1.0);
    } else if (fIsColor == 1 || fIsColor == 2 || fIsColor == 4) {
        fragColor = vec4(fColor);
    } else if (fIsColor == 3) {
        fragColor = vec4(random((fTime)*fPosition.xy),random((fTime+1.)*fPosition.yz),random((fTime+1.)*fPosition.zy),1.0);
    }*/
}

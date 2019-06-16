#version 330

const vec3 onColor = vec3(1.0, 1.0, 1.0);
const vec3 offColor = vec3(0.0, 0.0, 0.0);
const int numSquaresPerSide = 8;
in vec3 V; // object-space position

const vec3 myRed = vec3(0.6, 0.0, 0.0);
const vec3 myYellow = vec3(0.6, 0.5, 0.0);
const vec3 myBlue = vec3(0.0, 0.3, 0.6);
const vec3 myHalfSpace0 = vec3(0.31, 0.95, 0.0);
const vec3 myHalfSpace1 = vec3(-0.81, 0.59, 0.0);
const vec3 myHalfSpace2 = vec3(-0.81, -0.59, 0.0);
const vec3 myHalfSpace3 = vec3(0.31, -0.95, 0.0);
const vec3 myHalfSpace4 = vec3(1.0, 0.0, 0.0);
const float stripeThickness = 0.4; // 0 to 1
const float starSize = 0.2; // 0 to ~0.3
const float smoothEdgeTol = 0.005;

in vec4 fColor;
flat in int fIsColor;
in float fTime;
in vec4 fPosition;
in vec3 normalWorld;
in vec3 vertexPositionWorld;
in vec3 vertexToFragmentColor;

uniform vec3 lightPositionWorld;
uniform vec3 eyePositionWorld;
uniform vec4 ambientLight;
uniform int hideNumber;

out vec4 daColor;

void main()
{
    if (hideNumber == 0) {
        discard;
    }

    // Diffuse
    vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
    float brightness = dot(lightVectorWorld, normalize(normalWorld));
    vec4 diffuseLight = vec4(brightness, brightness, brightness, 1.0);

    // Specular
    vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
    vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
    float s = clamp(dot(reflectedLightVectorWorld, eyeVectorWorld), 0, 1);
    s = pow(s, 5);
    vec4 specularLight = vec4(s, s, s, 1);

    if (fIsColor == 3) {
        vec3 NV = normalize(V);
        // Map -1,1 to 0,numSquaresPerSide
        vec3 onOrOff = ((NV + 1.0) * float(numSquaresPerSide)) / 2.0;
        // mod 2 >= 1
        onOrOff = step(1.0, mod(onOrOff, 2.0));
        // 3-way xor
        onOrOff.x = step(0.5, mod(onOrOff.x + onOrOff.y + onOrOff.z, 2.0));
        daColor = vec4(mix(offColor, onColor, onOrOff.x),1.);

    } else if (fIsColor == 4) {
        vec3 myRed = vec3(1.0, 0.0, 0.0);
        vec3 myYellow = vec3(1.0, 1.0, 0.0);
        vec3 myGreen = vec3(0.0, 1.0, 0.0);
        vec3 myBlue = vec3(0.0, 0.0, 1.0);
        vec3 myWhite = vec3(1.0, 1.0, 1.0);
        vec3 myBlack = vec3(0.0, 0.0, 0.0);
        vec3 northHalfSpace = vec3(0.0, 0.0, 1.0);
        vec3 northeastHalfSpace = vec3(0.707, 0.0, 0.707);
        vec3 northwestHalfSpace = vec3(-0.707, 0.0, 0.707);
        float capSize = 0.03;
        float smoothEdgeTol = 0.005;
        vec3 NV = normalize(V);
        // Mirror half of ball across X and Z axes
        float mirror = (NV.x >= 0.0) ? 1.0 : -1.0;
        NV.xz *= mirror;
        // Check for north/south, east/west,
        // northeast/southwest, northwest/southeast
        vec4 distance;
        distance.x = dot(NV, northHalfSpace);
        distance.y = dot(NV, northeastHalfSpace);
        distance.z = dot(NV, northwestHalfSpace);
        // set up for white caps on top and bottom
        distance.w = abs(NV.y) - 1.0 + capSize;
        distance = smoothstep(vec4(0.0), vec4(smoothEdgeTol), distance);
        // red, green, red+green=yellow, and blue stripes
        vec3 surfColor = mix(myBlack, myRed, distance.x);
        surfColor += mix(myBlack, myGreen, distance.y*(1.0-distance.z));
        surfColor = mix(surfColor, myBlue, 1.0-distance.y);
        // white caps on top and bottom
        daColor = vec4(mix(surfColor, myWhite, distance.w),1.);
    } else if (fIsColor == 5) {
        vec4 distVector;
        float distScalar;
        vec3 NV = normalize(V);
        float myInOut = -3.0;
        // We need to perform 5 dot products, one for each edge of
        // the star. Perform first 4 in vector, 5th in scalar.
        distVector.x = dot(NV, myHalfSpace0);
        distVector.y = dot(NV, myHalfSpace1);
        distVector.z = dot(NV, myHalfSpace2);
        distVector.w = dot(NV, myHalfSpace3);
        distScalar = dot(NV, myHalfSpace4);
        // The half-space planes all intersect the origin. We must
        // offset them in order to give the star some size.
        distVector += starSize;
        distScalar += starSize;

        distVector = smoothstep(0.0, smoothEdgeTol, distVector);
        distScalar = smoothstep(0.0, smoothEdgeTol, distScalar);
        myInOut += dot(distVector, vec4(1.0));
        myInOut += distScalar;
        myInOut = clamp(myInOut, 0.0, 1.0);
        // red star on yellow background
        vec3 surfColor = mix(myYellow, myRed, myInOut);
        // blue stripe down middle
        myInOut = smoothstep(0.0, smoothEdgeTol, abs(NV.z) - stripeThickness);
        daColor = vec4(mix(myBlue, surfColor, myInOut),1.);
    } else if (fIsColor == 6) {
        vec3 NV = normalize(V);
        // Map -1,1 to 0,numSquaresPerSide
        float onOrOff = ((NV.z + 1.0) * float(numSquaresPerSide)) / 2.0;
        // mod 2 >= 1
        onOrOff = step(1.0, mod(onOrOff, 2.0));

        daColor = vec4(mix(offColor, onColor, onOrOff),1.);
    } else {
        daColor = vec4(fColor);
    }
    daColor = daColor + ambientLight + clamp(diffuseLight, 0, 1) + specularLight;
}

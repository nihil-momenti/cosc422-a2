varying vec3 normal, lightDir, eyeVec;

void main() {
    vec3 ecv;
    normal = gl_NormalMatrix * gl_Normal;
    ecv = vec3(gl_ModelViewMatrix * gl_Vertex);
    lightDir = vec3(gl_LightSource[0].position.xyz - ecv);
    eyeVec = -ecv;

    gl_Position = ftransform();
}

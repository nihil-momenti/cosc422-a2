varying vec3 normal, lightDir;

void main() {
    normal = normalize(gl_NormalMatrix * gl_Normal);
    lightDir = vec3(gl_LightSource[0].position - gl_ModelViewMatrix * gl_Vertex);

    gl_Position = ftransform();
}

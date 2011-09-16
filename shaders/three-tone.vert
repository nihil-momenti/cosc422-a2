varying vec3 normal, lightDir;

void main() {
    normal = gl_NormalMatrix * gl_Normal;
    lightDir = (gl_LightSource[0].position - gl_ModelViewMatrix * gl_Vertex).xyz;

    gl_Position = ftransform();
}

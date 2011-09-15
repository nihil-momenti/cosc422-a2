varying vec3 normal, lightDir, eyeVec;

void main() {
    float angle = 1.0 * gl_Vertex.z;
    float c = cos(angle),
          s = sin(angle);
    float x = c * gl_Vertex.x - s * gl_Vertex.y;
    float y = s * gl_Vertex.x + c * gl_Vertex.y;

    vec4 v = vec4(x, y, gl_Vertex.z, 1.0);

    vec3 ecv;
    normal = gl_NormalMatrix * gl_Normal;
    ecv = vec3(gl_ModelViewMatrix * v);
    lightDir = vec3(gl_LightSource[0].position.xyz - ecv);
    eyeVec = -ecv;

    gl_Position = gl_ModelViewProjectionMatrix * v;
}

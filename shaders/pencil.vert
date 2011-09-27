void main() {
    vec3 N = gl_NormalMatrix * gl_Normal;
    vec3 ecv = vec3(gl_ModelViewMatrix * gl_Vertex);
    vec3 L = normalize(vec3(gl_LightSource[0].position.xyz - ecv));

    gl_TexCoord[0].p = max(dot(N,L), 0.0);

    gl_Position = ftransform();
}

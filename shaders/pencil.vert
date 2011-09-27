void main() {
    vec3 N = normalize(gl_NormalMatrix * gl_Normal);
    vec3 ecv = (gl_ModelViewMatrix * gl_Vertex).xyz;
    vec3 L = normalize(gl_LightSource[0].position.xyz - ecv);

    gl_TexCoord[0].p = max(dot(N,L), 0.0);

    gl_Position = ftransform();
}

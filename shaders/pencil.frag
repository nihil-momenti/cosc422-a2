varying vec3 normal, lightDir;

uniform sampler3D texture;

void main() {
    vec3 N = normalize(normal);
    vec3 L = normalize(lightDir);

    float nDotl = max(dot(N,L), 0.0);

    gl_FragColor = texture3D(texture, vec3(gl_TexCoord[0].st, nDotl));
}

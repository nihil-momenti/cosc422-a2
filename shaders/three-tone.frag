varying vec3 normal, lightDir;

void main (void) {
    vec3 N = normalize(normal);
    vec3 L = normalize(lightDir);

    float nDotl = max(dot(N,L), 0.0);

    vec4 final_color = gl_FrontMaterial.diffuse;

    if (nDotl < 0.1) {
        final_color *= 0.6;
    } else if (nDotl > 0.85) {
        final_color *= 1.2;
    }

    gl_FragColor = final_color;
}

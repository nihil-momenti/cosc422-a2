varying vec3 normal, lightDir;

uniform sampler3D texture;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    vec3 N = normalize(normal);
    vec3 L = normalize(lightDir);

    float nDotl = max(dot(N,L), 0.0);

    float p = mix(nDotl, rand(gl_TexCoord[0].st), 0.0);
    gl_FragColor = texture3D(texture, vec3(gl_TexCoord[0].st, p));
}

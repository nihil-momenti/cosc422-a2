varying vec3 normal, lightDir, eyeVec;

void main (void) {
    vec3 N = normalize(normal);
    vec3 L = normalize(lightDir);
    vec3 E = normalize(eyeVec);
    vec3 R = reflect(-L, N);

    float nDotl = max(dot(N,L), 0.0);
    float spec = pow(max(dot(R, E), 0.0), gl_FrontMaterial.shininess);

    vec4 final_color = gl_LightSource[0].ambient  * gl_FrontMaterial.ambient
                     + gl_LightSource[0].diffuse  * gl_FrontMaterial.diffuse * nDotl
                     + gl_LightSource[0].specular * gl_FrontMaterial.specular * spec
                     + gl_LightModel.ambient      * gl_FrontMaterial.ambient;

    gl_FragColor = final_color;
}

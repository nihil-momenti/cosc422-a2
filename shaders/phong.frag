varying vec3 normal, lightDir, eyeVec;

void main (void) {
    vec4 final_color = gl_LightSource[0].ambient * gl_FrontMaterial.ambient
                     + gl_LightModel.ambient * gl_FrontMaterial.ambient;

    vec3 N = normalize(normal);
    vec3 L = normalize(lightDir);

    float nDotl = dot(N,L);

    if (nDotl < 0.0) {
      nDotl=0.0;
    }

    final_color += gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * nDotl;

    vec3 E = normalize(eyeVec);
    vec3 R = reflect(-L, N);

    float spec = pow(max(dot(R, E), 0.0), gl_FrontMaterial.shininess);
    final_color += gl_LightSource[0].specular * gl_FrontMaterial.specular * spec;

  ￼￼gl_FragColor = final_color;
}

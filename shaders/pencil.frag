uniform sampler3D texture;
uniform vec3 texture_size;

void main() {
    gl_FragColor = texture3D(texture, gl_TexCoord[0].stp * texture_size);
}

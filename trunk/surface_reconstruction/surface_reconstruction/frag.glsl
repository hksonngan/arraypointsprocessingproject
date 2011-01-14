uniform sampler3D myTexture;
uniform float pCoord;

uniform float multCoeff;

void main(void) {
    //gl_FragColor = vec4 ( gl_TexCoord[0].st, 0, 1 );

    gl_FragColor = vec4(texture3D(myTexture, vec4(1 - gl_TexCoord[0].t, 1 - gl_TexCoord[0].s, pCoord, 0.0)).a) * multCoeff;
    //gl_FragColor = vec4(texture3D(myTexture, vec4(0.0, 0.01, 0.5, 0.0)).a);
}

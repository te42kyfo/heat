#version 130

uniform sampler2D tex;

void main(void){
	gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	gl_FragColor.r = texture2D(tex, gl_TexCoord[0].st ).r;
	//gl_FragColor.st = gl_TexCoord[0].st;
}



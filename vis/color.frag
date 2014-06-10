#version 130

uniform sampler2D tex;

void main(void){

	float texValue = texture2D(tex, gl_TexCoord[0].st ).r;




	texValue *= 0.0019;

	/*	if( texValue < 0.5) {
		gl_FragColor = vec4( texValue*10.0,
							 texValue*4.0-1.0,
							 0.0,
							 1.0);
	} else {

							 }*/

	gl_FragColor = vec4( texValue*4.0,
						 texValue*2.0-0.25,
						 texValue*1.0-0.375,
						 1.0);


}

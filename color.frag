#version 130

uniform sampler2D tex;

void main(void){

	float texValue = texture2D(tex, gl_TexCoord[0].st ).r;



	texValue = log(texValue);

	texValue *= 0.2;

	if( texValue < 0.5) {
		gl_FragColor = vec4( texValue*1.5,
							 0,
							 0.0,
							 1.0);
	} else {
		gl_FragColor = vec4( 0.25 + texValue,
							 (texValue-0.5)*3.0f,
							 (texValue-0.5),
							 1.0);
	}




}

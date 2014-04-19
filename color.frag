#version 130

void main(void){
    gl_FragColor = gl_FragCoord / 600.0;
	gl_FragColor.a = 1.0;
	//	gl_FragColor.b = 0.0;
}



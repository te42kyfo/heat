void initGL() {
	glShadeModel( GL_FLAT );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glDisable(GL_DEPTH_TEST);


	std::cout << glGetString(GL_VENDOR) << "\n";
	std::cout << glGetString(GL_RENDERER) << "\n";
	std::cout << glGetString(GL_VERSION) << "\n";
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
}


void setViewport( int width, int height ) {
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho( (float) -width/height, (float) width/height, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void render() {

	static unsigned int frame_number = 0;


	frame_number++;


    glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();

	GLfloat vertices[] = { 0.0, 0.0, 0.0,
						   1.0, 0.0, 0.0,
						   0.0, 1.0, 0.0,
						   1.0, 1.0, 0.0,
						   0.5, 2.0, 0.0 };

	GLubyte indices[]  = { 0, 1, 2,
						   3, 2, 1,
						   2, 3, 4 };

	GLfloat colors[] = { 1.0, 1.0, 1.0,
						 1.0, 1.0, 1.0,
						 1.0, 1.0, 1.0,
						 1.0, 1.0, 1.0,
						 1.0, 0.0, 0.0 };




	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	for( size_t i = 0; i < 10; i++) {
		glTranslatef( ((i*23+17)%11) / 11.0-0.5, ((i*26+1)%11) / 11.0-0.5, 0.0);
		glScalef(0.1, 0.1, 0.1);
		glRotatef(frame_number/-2.0*(i+3), 0.0, 0.0, 1.0 );
		glTranslatef( -0.5, -0.75, 0.0);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_BYTE, indices);
		glLoadIdentity();
	}


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);





	glFlush();
	glLoadIdentity();
}

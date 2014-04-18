void initGL() {
	glShadeModel( GL_SMOOTH );
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
	glScalef(0.3, 0.3, 0.3);

	glRotatef(frame_number/-2.0, 0.0, 0.0, 1.0 );

	glTranslatef(0, 1.0, 0.0);


	glColor3f(1.0, 1.0, 1.0);
    glBegin( GL_TRIANGLES );            /* Drawing Using Triangles */
      glVertex3f(  0.0f,  1.0f, 0.0f ); /* Top */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
    glEnd( );                           /* Finished Drawing The Triangle */

	glTranslatef(0, -2.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
    glBegin( GL_QUADS );                /* Draw A Quad */
      glVertex3f( -1.0f,  1.0f, 0.0f ); /* Top Left */
      glVertex3f(  1.0f,  1.0f, 0.0f ); /* Top Right */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
    glEnd( );                           /* Done Drawing The Quad */

	glFlush();
	glLoadIdentity();
}

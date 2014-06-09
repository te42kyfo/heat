#include <vector>
#include <iostream>

#include <cmath>
#include "sdl_gl.hpp"


using namespace std;



void SdlGl::initDrawSlice() {
	glShadeModel( GL_FLAT );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glDisable(GL_DEPTH_TEST);

	color_program = loadShader( "color.vert", "color.frag" );

}



void SdlGl::drawSlice() {

	frame_number++;

    glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();


	vector<GLfloat> vertices = { -1.0, -1.0, 0.0,
								 1.0, -1.0, 0.0,
								 -1.0,  1.0, 0.0,
								 1.0,  1.0, 0.0 };
	vector<GLfloat> texCoords = { 0.0, 0.0,
								  1.0, 0.0,
								  0.0, 1.0,
								  1.0, 1.0};

	vector<GLubyte> indices  = { 0, 1, 2,
								 1, 2, 3 };


	if( slice_depth < 0.0) slice_depth = 0;
	if( slice_depth >= grid->phys_dim[2]) slice_depth = grid->phys_dim[2];

	size_t slice_offset = grid->p2g(slice_depth, 2);
	if( slice_offset >= grid->grid_dim[2]) slice_offset = grid->grid_dim[2]-1;

	GLuint texId;
	glGenTextures(1, &texId);
	glBindTexture( GL_TEXTURE_2D, texId);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_R32F,
				  grid->grid_dim[0], grid->grid_dim[1], 0,
				  GL_RED, GL_FLOAT,
				  grid->data.data() + grid->idx( 0, 0, slice_offset ) );



	GLint texUloc = glGetUniformLocation(color_program, "tex");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D,  texId);
    glUniform1i( texUloc, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	glUseProgram(color_program);



	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices.data() );
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data() );

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, indices.data() );

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDeleteTextures(1, &texId);

	glFlush();
	glLoadIdentity();
}

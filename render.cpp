#include <vector>
#include <fstream>
#include <string>
#include <iostream>
//#include <SDL2/SDL_opengl.h>
#include <GL/glew.h>
#include <cmath>
#include "render.hpp"
using namespace std;


string Render::readShaderFile(const string fileName) {
	try {
		std::ifstream t( fileName.c_str() );
		return std::string( (std::istreambuf_iterator<char>(t)),
							std::istreambuf_iterator<char>());
	} catch( std::exception& e) {
		std::cout << fileName << " - " << "readShaderFile: " << e.what() << "\n";
        return string();
    }
}

GLuint Render::loadShader(string vshader, string fshader) {
    GLcharARB log[5000];
    GLsizei length;

    string vertex_shader = readShaderFile( vshader );
    string fragment_shader = readShaderFile( fshader );
    char const * my_fragment_shader_source = fragment_shader.c_str();
    char const * my_vertex_shader_source = vertex_shader.c_str();


    GLuint program = glCreateProgramObjectARB();
    GLuint vertex = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    GLuint fragment = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

    glShaderSourceARB( vertex, 1, &my_vertex_shader_source, NULL);
    glShaderSourceARB( fragment, 1, &my_fragment_shader_source, NULL);
    glCompileShader( vertex);
    glCompileShader( fragment);
    glAttachObjectARB( program, vertex);
    glAttachObjectARB( program, fragment);
    glLinkProgramARB( program);

    glGetInfoLogARB( vertex, 5000, &length, log);
    if( length > 0) std::cout << "Vertex Shader: "  << log << "\n";
    glGetInfoLogARB( fragment, 5000, &length, log);
    if( length > 0) std::cout << "Fragment Shader: " << log << "\n";
    glGetInfoLogARB( program, 5000, &length, log);
    if( length > 0) std::cout << "Progrgam: " << log << "\n";

	return program;
}

void Render::initGL() {
	glewInit();
	glShadeModel( GL_FLAT );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glDisable(GL_DEPTH_TEST);


	std::cout << glGetString(GL_VENDOR) << "\n";
	std::cout << glGetString(GL_RENDERER) << "\n";
	std::cout << glGetString(GL_VERSION) << "\n";
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

	color_program = loadShader( "color.vert", "color.frag" );
	frame_number = 0;



}

void Render::setViewport( int width, int height ) {
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho( (float) -width/height, (float) width/height, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Render::render() {

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

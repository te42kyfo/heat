#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <sys/time.h>

using namespace std;

struct  SDL_State {
    SDL_Window* window;
    SDL_Window* window2;
    SDL_Renderer* renderer;
	SDL_GLContext  gl_context;
	SDL_GLContext  gl_context2;
};


double dtime() {
	double tseconds = 0;
	struct timeval t;
	gettimeofday( &t, NULL);
	tseconds = (double) t.tv_sec + (double) t.tv_usec*1.0e-6;
	return tseconds;
}

void setViewport( int width, int height ) {
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho( (float) -width/height, (float) width/height, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void SDL_die( string error ) {
	cout << "Fatal error in " << error << ": " << SDL_GetError() << "\n";
	exit(EXIT_FAILURE);
}

void initDisplay(SDL_State& sdl) {

	if( SDL_Init(SDL_INIT_VIDEO) == -1) SDL_die( "SDL_Init" );


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);



    // create the sdl2 window
    sdl.window = SDL_CreateWindow( "HEAT", SDL_WINDOWPOS_CENTERED,
								   SDL_WINDOWPOS_CENTERED, 600, 500,
								   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if( sdl.window == nullptr) SDL_die("SDL_CreateWindow");
	sdl.gl_context = SDL_GL_CreateContext(sdl.window);
	if( sdl.gl_context == nullptr) SDL_die( "SDL_GL_CreateContext");
	SDL_GL_MakeCurrent(sdl.window, sdl.gl_context);
	SDL_GL_SetSwapInterval(1);

	setViewport(1200, 800);

    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glDisable(GL_DEPTH_TEST);


	// create the sdl2 window2
    sdl.window2 = SDL_CreateWindow( "HEAT2", SDL_WINDOWPOS_UNDEFINED,
								   SDL_WINDOWPOS_UNDEFINED, 600, 500,
								   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if( sdl.window2 == nullptr) SDL_die("SDL_CreateWindow");
    sdl.gl_context2 = SDL_GL_CreateContext(sdl.window);
	if( sdl.gl_context2 == nullptr) SDL_die( "SDL_GL_CreateContext");


	SDL_GL_MakeCurrent(sdl.window2, sdl.gl_context2);
	SDL_GL_SetSwapInterval(1);
	setViewport(1200, 800);
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glDisable(GL_DEPTH_TEST);



	cout << glGetString(GL_VENDOR) << "\n";
	cout << glGetString(GL_RENDERER) << "\n";
	cout << glGetString(GL_VERSION) << "\n";
	cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";


}


void render(int windowId) {

	static unsigned int frame_number = 0;

	frame_number++;


    glClearColor( 0.1f, 0.0f, 0.1f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	glScalef(0.3, 0.3, 0.3);

	if( windowId == 1) {
		glRotatef( frame_number/2.0, 0.0, 0.0, 1.0 );
	} else {
		glRotatef(frame_number/-2.0, 0.0, 0.0, 1.0 );
	}

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



int main(int argc, char *argv[]) {


	SDL_State sdl;

	initDisplay(sdl);

	SDL_Event e;
	bool quit = false;
	double frame_time = dtime();
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}

			if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
				case SDLK_q:
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
			}
			if(e.type == SDL_WINDOWEVENT) {
				if( e.window.event == SDL_WINDOWEVENT_RESIZED) {
					SDL_GL_MakeCurrent(sdl.window, sdl.gl_context);
					setViewport( e.window.data1, e.window.data2 );
					SDL_GL_MakeCurrent(sdl.window2, sdl.gl_context2);
					setViewport( e.window.data1, e.window.data2 );
				}
			}

		}

		SDL_GL_MakeCurrent(sdl.window, sdl.gl_context);
		render(0);
		SDL_GL_SwapWindow(sdl.window);

		SDL_GL_MakeCurrent(sdl.window2, sdl.gl_context2);
		render(1);
		SDL_GL_SwapWindow(sdl.window2);

		SDL_Delay(35);

		double new_frame_time = dtime();
		std::cout << 1.0 / (new_frame_time - frame_time) << "\n";
		frame_time = dtime();
	}


	SDL_Quit();
}

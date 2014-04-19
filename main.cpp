#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <sys/time.h>

#include "render.hpp"

using namespace std;

struct  SDL_State {
    SDL_Window* window;
	SDL_GLContext  gl_context;
};


double dtime() {
	double tseconds = 0;
	struct timeval t;
	gettimeofday( &t, NULL);
	tseconds = (double) t.tv_sec + (double) t.tv_usec*1.0e-6;
	return tseconds;
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
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);


    sdl.window = SDL_CreateWindow( "HEAT", SDL_WINDOWPOS_UNDEFINED,
								   SDL_WINDOWPOS_UNDEFINED, 800, 600,
								   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if( sdl.window == nullptr) SDL_die("SDL_CreateWindow");

	sdl.gl_context = SDL_GL_CreateContext(sdl.window);
	if( sdl.gl_context == nullptr) SDL_die( "SDL_GL_CreateContext");

	SDL_GL_SetSwapInterval(1);
}


int main(int argc, char *argv[]) {


	SDL_State sdl;
	Render render;

	initDisplay(sdl);
	render.initGL();
	render.setViewport(800, 600);


	SDL_Event e;
	bool quit = false;
	//double frame_time = dtime();
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
					render.setViewport( e.window.data1, e.window.data2 );
				}
			}


		}

		render.render();
		SDL_GL_SwapWindow(sdl.window);

		//	SDL_Delay(20);

		//double new_frame_time = dtime();
		//std::cout << 1.0 / (new_frame_time - frame_time) << "\n";
		//frame_time = dtime();
	}


	SDL_Quit();
}

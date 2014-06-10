#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <cstdio>

#include <sys/time.h>

#include "sdl_gl.hpp"
#include "simulation.hpp"

using namespace std;


double dtime() {
	double tseconds = 0;
	struct timeval t;
	gettimeofday( &t, NULL);
	tseconds = (double) t.tv_sec + (double) t.tv_usec*1.0e-6;
	return tseconds;
}


int main(int argc, char *argv[]) {




	Simulation sim( 1.0, 1.0, 1.0,
					100, 100, 100);



	sim.lambda->fillPhysCube( 0.0f, 0.0f, 0.0f,
							  1.0f, 1.0f, 1.0f,
							  0.1);


	sim.lambda->fillPhysCube( 0.3f, 0.3f, 0.0f,
							  0.7f, 0.7f, 1.0f,
							  1.0f);

	sim.lambda->fillPhysCube( 0.4f, 0.4f, 0.0f,
							  0.6f, 0.6f, 1.0f,
							  0.011f);

	sim.source->fillPhysCube( 0.4f, 0.4f, 0.0f,
							  0.6f, 0.6f, 1.0f,
							  -400.0f);

	sim.source->fillPhysCube( 0.4f, 0.47f, 0.47f,
							  0.42f, 0.53f, 0.53f,
							  -10000000.0f);


	sim.capacity->fillPhysCube( 0.0f, 0.0f, 0.0f,
								1.0f, 1.0f, 1.0f,
								1.0f);





	SdlGl vis;

	vis.initDisplay();
	vis.initDrawSlice();
	vis.setViewport(800, 600);

	float slice_depth = 0.5;
	auto grid = sim.temp_A;

	SDL_Event e;
	bool quit = false;

	double frame_time = dtime();
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
				case SDLK_UP:
					slice_depth += 0.1;
					break;
				case SDLK_DOWN:
					slice_depth -= 0.1;
					break;
				default:
					break;
				}
			}



			if(e.type == SDL_WINDOWEVENT) {
				if( e.window.event == SDL_WINDOWEVENT_RESIZED) {
					vis.setViewport( e.window.data1, e.window.data2 );
				}
			}


		}


		double now = dtime();

		std::cout << "\r" << 1.0/ ( (now-frame_time) );

		frame_time = now;

		for(size_t i = 0; i < 6; i++) {
			sim.step();
		}


		if( slice_depth < 0.0) slice_depth = 0;
		if( slice_depth >= grid->phys_dim[2]) slice_depth = grid->phys_dim[2];

		size_t slice_offset = grid->p2g(slice_depth, 2);
		if( slice_offset >= grid->grid_dim[2]) slice_offset = grid->grid_dim[2]-1;

		vis.drawSlice(grid->data.data() + grid->idx( 0, 0, slice_offset ),
					  grid->grid_dim[0], grid->grid_dim[1]);
		SDL_GL_SwapWindow( vis.window);

	}


	SDL_Quit();
}

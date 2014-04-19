#include "simulation.hpp"


void Simulation::fillCube( std::vector<float>& grid,
						   size_t x1, size_t y1, size_t z1,
						   size_t x2, size_t y2, size_t z2,
						   float value) {


	for( size_t z = z1; z < z2; z++) {
		for( size_t y = y1; y < y2; y++) {
			for(size_t x = x1; x < x2; x++) {
				grid[idx(x,y,z)] = value;
			}
		}
	}
}


void Simulation::step() {

	float* pA = temp_A.data();
	float* pB = temp_B.data();



	for( size_t z = 1; z < grid_dim[2]-1; z++) {
		for( size_t y = 1; y < grid_dim[1]-1; y++) {
			for(size_t x = 1; x < grid_dim[0]-1; x++) {
				pB[idx(x,y,z)] = (1.0f/6.0f) *
					( pA[idx(x+1,y  ,z  )] +
					  pA[idx(x-1,y  ,z  )] +
					  pA[idx(x  ,y+1,z  )] +
					  pA[idx(x  ,y-1,z  )] +
					  pA[idx(x  ,y  ,z+1)] +
					  pA[idx(x  ,y  ,z-1)] );
			}
		}
	}
	swap( temp_A, temp_B );


}

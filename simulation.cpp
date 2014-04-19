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


	#pragma omp parallel for
	for( size_t z = 1; z < grid_dim[2]-1; z++) {
		for( size_t y = 1; y < grid_dim[1]-1; y++) {
			for(size_t x = 1; x < grid_dim[0]-1; x++) {
				pB [grid_dim[0]*grid_dim[1]*z +
					grid_dim[0]*y + x ]
					= (1.0f/6.0f) *
					( pA[grid_dim[0]*grid_dim[1]*(z) +
						 grid_dim[0]*(y) +x+1] +
					  pA[grid_dim[0]*grid_dim[1]*(z) +
						 grid_dim[0]*(y) +x-1] +
					  pA[grid_dim[0]*grid_dim[1]*(z) +
						 grid_dim[0]*(y+1) +x] +
					  pA[grid_dim[0]*grid_dim[1]*(z) +
						 grid_dim[0]*(y-1) +x] +
					  pA[grid_dim[0]*grid_dim[1]*(z+1) +
						 grid_dim[0]*(y) +x] +
					  pA[grid_dim[0]*grid_dim[1]*(z-1) +
						 grid_dim[0]*(y) +x] );
			}
		}
	}

	swap( temp_A, temp_B );


}

#include "simulation.hpp"
#include "iostream"




constexpr size_t didx(size_t x, size_t y, size_t z,
					 size_t d0, size_t d1) {
	return z*d0*d1 + y*d0 + x;
}

void Simulation::step() {

	float* pA = temp_A->data.data();
	float* pB = temp_B->data.data();
	float* pSource = source->data.data();


	size_t const gd0 = grid_dim[0];
	size_t const gd1 = grid_dim[1];


	float dx = phys_dim[0] / grid_dim[0];
	float dy = phys_dim[1] / grid_dim[1];
	float dz = phys_dim[2] / grid_dim[2];

	float dx2 = dx*dx;
	float dy2 = dy*dy;
	float dz2 = dz*dz;

	float kx = 1.0f/dx2 / (2.0f/dx2 + 2.0f/dy2 + 2.0f/dz2);
	float ky = 1.0f/dy2 / (2.0f/dx2 + 2.0f/dy2 + 2.0f/dz2);
	float kz = 1.0f/dz2 / (2.0f/dx2 + 2.0f/dy2 + 2.0f/dz2);
	float kr = 1.0      / (2.0f/dx2 + 2.0f/dy2 + 2.0f/dz2);

	//	cout << kx << " " << ky << " " << kz << "\n";

	#pragma omp parallel for
	for( size_t z = 1; z < grid_dim[2]-1; z++) {
		for( size_t y = 1; y < grid_dim[1]-1; y++) {
			for(size_t x = 1; x < grid_dim[0]-1; x++) {
				pB [didx(x, y, z, gd0, gd1)] =
					kx * (  pA[didx(x+1,y  ,z  , gd0, gd1)] +
						    pA[didx(x-1,y  ,z  , gd0, gd1)] ) +
					ky * (  pA[didx(x  ,y+1,z  , gd0, gd1)] +
						    pA[didx(x  ,y-1,z  , gd0, gd1)] ) +
					kz * (  pA[didx(x  ,y  ,z+1, gd0, gd1)] +
						    pA[didx(x  ,y  ,z-1, gd0, gd1)] ) -
					kr*pSource[didx(x  ,y  ,z  , gd0, gd1)];
			}
		}
	}

	swap( temp_A, temp_B );


}

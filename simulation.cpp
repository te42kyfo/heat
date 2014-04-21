#include "simulation.hpp"
#include "iostream"


using namespace std;

constexpr size_t didx(size_t x, size_t y, size_t z,
					 size_t d0, size_t d1) {
	return z*d0*d1 + y*d0 + x;
}

void Simulation::step() {

	float* pA = temp_A->data.data();
	float* pB = temp_B->data.data();
	float* pS = source->data.data();
	float* pL = lambda->data.data();
	//float* pCapacity = capacity->data.data();


	size_t const gd0 = grid_dim[0];
	size_t const gd1 = grid_dim[1];


	float dx = phys_dim[0] / grid_dim[0];
	float dy = phys_dim[1] / grid_dim[1];
	float dz = phys_dim[2] / grid_dim[2];


	float idx2 = 1.0/(dx*dx);
	float idy2 = 1.0/(dy*dy);
	float idz2 = 1.0/(dz*dz);



	#pragma omp parallel for
	for( size_t z = 1; z < grid_dim[2]-1; z++) {
		for( size_t y = 1; y < grid_dim[1]-1; y++) {
			for(size_t x = 1; x < grid_dim[0]-1; x++) {
				float inv_denom =
					1.0f / ( ( pL[didx(x+1, y, z, gd0, gd1)] +
							   pL[didx(x-1, y, z, gd0, gd1)] ) * idx2 +
							 ( pL[didx(x, y+1, z, gd0, gd1)] +
							   pL[didx(x, y-1, z, gd0, gd1)] ) * idy2 +
							 ( pL[didx(x, y, z+1, gd0, gd1)] +
							   pL[didx(x, y, z-1, gd0, gd1)] ) * idz2 +
							 2.0f*(idx2+idy2+idz2)*pL[didx(x, y, z, gd0, gd1)] );



				float k1 = pA[didx(x+1, y, z, gd0, gd1)] * idx2 *
					( pL[didx(x+1, y, z, gd0, gd1)] +  pL[didx(x, y, z, gd0, gd1)] );
				float k2 = pA[didx(x-1, y, z, gd0, gd1)] * idx2 *
					( pL[didx(x-1, y, z, gd0, gd1)] +  pL[didx(x, y, z, gd0, gd1)] );
				float k3 = pA[didx(x, y+1, z, gd0, gd1)] * idy2 *
					( pL[didx(x, y+1, z, gd0, gd1)] +  pL[didx(x, y, z, gd0, gd1)] );
				float k4 = pA[didx(x, y-1, z, gd0, gd1)] * idy2 *
					( pL[didx(x, y-1, z, gd0, gd1)] +  pL[didx(x, y, z, gd0, gd1)] );
				float k5 = pA[didx(x, y, z+1, gd0, gd1)] * idz2 *
					( pL[didx(x, y, z+1, gd0, gd1)] +  pL[didx(x, y, z, gd0, gd1)] );
				float k6 = pA[didx(x, y, z-1, gd0, gd1)] * idz2 *
					( pL[didx(x, y, z-1, gd0, gd1)] +  pL[didx(x, y, z, gd0, gd1)] );

				pB[didx(x, y, z, gd0, gd1)] =
					( k1+k2+k3+k4+k5+k6-
					  pS[didx(x, y, z, gd0, gd1)]) * inv_denom;

			}
		}
	}

	swap( temp_A, temp_B );


}

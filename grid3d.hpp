#ifndef GRID3D_HPP
#define GRID3D_HPP

#include <vector>


template<class T>
class Grid3D {
public:

	Grid3D(  float pd1, float pd2, float pd3,
			 size_t d1, size_t d2, size_t d3 ) :
		grid_dim {d1, d2, d3},
		phys_dim {pd1, pd2, pd3},
		data( d1*d2*d3 ) {};


	size_t idx(size_t x1, size_t x2, size_t x3) const {
		return x3 * grid_dim[0]*grid_dim[1] + x2*grid_dim[0] + x1;
	}

	size_t pidx( float x, float y, float z) const {
		return idx( p2g(x, 0), p2g(y, 1), p2g(z, 2) );
	}

	size_t p2g( float pv, size_t dim ) const {
		return (pv/phys_dim[dim]) * grid_dim[dim] ;
	}
	float g2p( size_t gv, size_t dim ) const {
		return  (phys_dim[dim]* gv) /grid_dim[dim];
	}

	void fillCube( size_t x1, size_t y1, size_t z1,
				   size_t x2, size_t y2, size_t z2,
				   float value) {
		for( size_t z = z1; z < z2; z++) {
			for( size_t y = y1; y < y2; y++) {
				for(size_t x = x1; x < x2; x++) {
					data[idx(x,y,z)] = value;
				}
			}
		}
	}

	void fillPhysCube( float x1, float y1, float z1,
					   float x2, float y2, float z2,
					   float value) {

		fillCube( p2g(x1, 0), p2g(y1, 1), p2g(z1, 2),
				  p2g(x2, 0), p2g(y2, 1), p2g(z2, 2),
				  value);
	}


	const size_t grid_dim[3];
	const float phys_dim[3];
	std::vector<T> data;

};

#endif //GRID3D_HPP

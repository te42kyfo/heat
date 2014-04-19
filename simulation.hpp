#include <vector>

using namespace std;

class Simulation {
public:
	Simulation( float pd1, float pd2, float pd3,
				size_t d1, size_t d2, size_t d3) :
		grid_dim {d1, d2, d3},
		phys_dim {pd1, pd2, pd3},
		temp_A( d1*d2*d3, 0.0),
		temp_B( d1*d2*d3, 0.0),
		lambda( d1*d2*d3, 0.0),
		source( d1*d2*d3, 0.0) {};

	size_t idx(size_t x1, size_t x2, size_t x3) const {
		return x3 * grid_dim[0]*grid_dim[1] + x2*grid_dim[0] + x1;
	}

	size_t p2g( float pv, size_t dim ) const {
		return (pv/phys_dim[dim]) * grid_dim[dim] ;
	}
	float g2p( size_t gv, size_t dim ) const {
		return  (phys_dim[dim]* gv) /grid_dim[dim];
	}

	void fillCube( std::vector<float>& grid,
				   size_t x1, size_t y1, size_t z1,
				   size_t x2, size_t y2, size_t z2,
				   float value);


	void step();

	const size_t grid_dim[3];
	const float phys_dim[3];

	std::vector<float> temp_A;
	std::vector<float> temp_B;
	std::vector<float> lambda;
	std::vector<float> source;

};




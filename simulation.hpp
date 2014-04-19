#include <vector>
#include <memory>
#include "grid3d.hpp"




class Simulation {
public:
	Simulation( float pd1, float pd2, float pd3,
				size_t d1, size_t d2, size_t d3) :
		grid_dim {d1, d2, d3},
		phys_dim {pd1, pd2, pd3},
		temp_A( std::make_shared<Grid3D<float>> ( pd1, pd2, pd3,
												  d1, d2, d3)),
		temp_B( std::make_shared<Grid3D<float>> ( pd1, pd2, pd3,
												  d1, d2, d3)),
		lambda( std::make_shared<Grid3D<float>> ( pd1, pd2, pd3,
												  d1, d2, d3)),
		source( std::make_shared<Grid3D<float>> ( pd1, pd2, pd3,
												  d1, d2, d3)) {};




	void step();

	const size_t grid_dim[3];
	const float phys_dim[3];

	std::shared_ptr<Grid3D<float>> temp_A;
	std::shared_ptr<Grid3D<float>> temp_B;
	std::shared_ptr<Grid3D<float>> lambda;
	std::shared_ptr<Grid3D<float>> source;


};

#include <vector>


class Render {
private:
	std::string readShaderFile( const std::string fileName);
	GLuint loadShader(std::string vshader, std::string fshader);

	GLuint color_program;
	unsigned int frame_number;

	std::vector<float> grid_data;
	size_t grid_width;
	size_t grid_height;

public:
	void setViewport(int width, int height);
	void initGL();
	void render();

};












#include "Rasterize.h"
#include <fstream>

int main() 
{
	glm::mat4 viwePortMatrix = Math::GetViewPortMatrix(0, 0, 1920, 1080);
	Rasterize rasterize;

	Vertex V1(glm::vec3(-0.5, -0.5, 0), glm::vec4(255, 0, 0, 0));
	Vertex V2(glm::vec3(0.5, -0.5, 0), glm::vec4(0, 255, 0, 0));
	Vertex V3(glm::vec3(0, 0.5, 0), glm::vec4(0, 0, 255, 0));

	V2F o1 = rasterize.shader.VertexShader(V1);
	V2F o2 = rasterize.shader.VertexShader(V2);
	V2F o3 = rasterize.shader.VertexShader(V3);

	o1.windowPos = viwePortMatrix * o1.windowPos;
	o2.windowPos = viwePortMatrix * o2.windowPos;
	o3.windowPos = viwePortMatrix * o3.windowPos;


	rasterize.FrontBuffer.ClearBuffer(glm::vec4(0, 255, 0, 0));
	rasterize.ScanTriangle(o1, o2, o3);

	std::ofstream outImage;
	outImage.open("result.ppm");
	int width = rasterize.width;
	int height = rasterize.height;
	const std::vector<unsigned char>& colorBuffer = rasterize.colorBuffer;
	outImage << "P3\n" << width << ' ' << height << "\n255\n";
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			unsigned int r = (unsigned int)colorBuffer[(i * width + j) * 4];
			unsigned int g = (unsigned int)colorBuffer[(i * width + j) * 4 + 1];
			unsigned int b = (unsigned int)colorBuffer[(i * width + j) * 4 + 2];

			outImage << r << ' ' << g << ' ' << b << '\n';
		}
	}
}
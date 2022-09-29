#include "Rasterize.h"
#include <cstdio>
#include <iostream>
#include <fstream>


int main() 
{
	
	Rasterize rasterize(800, 600);
	glm::mat4 viwePortMatrix = Math::GetViewPortMatrix(0, 0, rasterize.width, rasterize.height);

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
	const std::vector<unsigned int>& colorBuffer = rasterize.colorBuffer;
	outImage << "P3\n" << width << ' ' << height << "\n255\n";
	for (int i = height - 1; i >= 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			unsigned int r = colorBuffer[(i * width + j) * 4];
			unsigned int g = colorBuffer[(i * width + j) * 4 + 1];
			unsigned int b = colorBuffer[(i * width + j) * 4 + 2];
			outImage << r << ' ' << g << ' ' << b << '\n';
		}
	}
	outImage.close();
}
#include "tgaimage.h"
#include "model.h"
#include <iostream>
#include "Draw.h"
using namespace std;

int main() 
{
	Draw draw;
	TGAImage image(draw.GetWidth(),draw.GetHeight(), TGAImage::RGB);
	Model* model = new Model("obj\\african_head.obj");
	//draw.DrawModelByColor(model, image);
	Vec3f lightdir(0, 0, -1);
	draw.DrawModelWithLight(model, image, lightdir);

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

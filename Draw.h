#pragma once
#include "tgaimage.h"
#include "model.h"
#include <iostream>
#include <vector>
class Draw
{
private:
	int width = 800;
	int height = 600;
	float* zBuffer = new float[800 * 600+1];
	
public:
	TGAImage* image = new TGAImage(width, height, TGAImage::RGB);

	Draw()
	{
		for (int i = 0; i < 800 * 600+1; i++)
		{
			zBuffer[i] = -999.0f;
		}
	}
	~Draw()=default;
	int GetWidth() const 
	{ 
		return width; 
	}
	int GetHeight() const
	{
		return height;
	}
	void SetWidth(int w)
	{
		width = w;
		delete(image);
		delete(zBuffer);
		zBuffer = new float[height * width];
		image = new TGAImage(width, height, TGAImage::RGB);
	}
	void SetHeight(int h)
	{
		height = h;
		delete(image);
		delete(zBuffer);
		zBuffer = new float[height * width];
		image = new TGAImage(width, height, TGAImage::RGB);
	}
	void line(int x0, int y0, int x1, int y1, TGAImage& image,const TGAColor& color = TGAColor(255, 255, 255, 255))
	{
		bool steep = false;
		if (std::abs(x0 - x1) < std::abs(y0 - y1))
		{
			std::swap(x0, y0);
			std::swap(x1, y1);
			steep = true;
		}
		if (x0 > x1)
		{
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		int dx = x1 - x0;
		int dy = y1 - y0;
		int dyerr2 = std::abs(dy) * 2;
		int err2 = 0;
		int y = y0;
		for (int x = x0; x <= x1; x++)
		{
			if (steep)
				image.set(y, x, color);
			else
				image.set(x, y, color);
			err2 += dyerr2;
			if (err2 > dx)
			{
				y += (y1 > y0 ? 1 : -1);
				err2 -= dx * 2;
			}
		}
	}
	void DrawModelByLine(Model* model, TGAImage& image,const TGAColor& color=TGAColor(255,255,255,255))
	{
		if (model)
		{
			for (int i = 0; i < model->nfaces(); i++)
			{
				std::vector<int> face = model->face(i);
				for (int j = 0; j < 3; j++)
				{
					Vec3f v0 = model->vert(face[j]);
					Vec3f v1 = model->vert(face[(j + 1) % 3]);
					int x0 = (v0.x + 1.) * width / 2.;
					int y0 = (v0.y + 1.) * height / 2.;
					int x1 = (v1.x + 1.) * width / 2.;
					int y1 = (v1.y + 1.) * height / 2.;
					line(x0, y0, x1, y1, image, color);
				}
			}
		}	
		else
		{
			std::cout << "model missing";
		}		
	}
	Vec3f& Barycentric(const std::vector<Vec3f>& trianglePoints, const Vec2i& p)
	{
		
		Vec3f u;
		const Vec3f& a = trianglePoints[0];
		const Vec3f& b = trianglePoints[1];
		const Vec3f& c = trianglePoints[2];
		u.x = (-(p.x - b.x) * (c.y - b.y) + (p.y - b.y) * (c.x - b.x)) / (float)((-(a.x - b.x) * (c.y - b.y) + (a.y - b.y) * (c.x - b.x)) + 0.01f);
		u.y = (-(p.x - c.x) * (a.y - c.y) + (p.y - c.y) * (a.x - c.x)) / (float)((-(b.x - c.x) * (a.y - c.y) + (b.y - c.y) * (a.x - c.x)) + 0.01f);
		u.z = 1 - u.x - u.y;
		return u;
	}
	void Traingle(const std::vector<Vec3f>& trianglePoints,float* zBuffer,TGAImage& image, const TGAColor& color = TGAColor(255, 255, 255, 255))
	{
		const Vec3f& a = trianglePoints[0];
		const Vec3f& b = trianglePoints[1];
		const Vec3f& c = trianglePoints[2];
		Vec2i boxmin;
		Vec2i boxmax;
		boxmin.x = std::min(a.x, std::min(b.x, c.x));
		boxmin.y = std::min(a.y, std::min(b.y, c.y));
		boxmax.x = std::max(a.x, std::max(b.x, c.x));
		boxmax.y = std::max(a.y, std::max(b.y, c.y));
		Vec3f p;
		for (p.x = boxmin.x; p.x <= boxmax.x; p.x++)
		{
			for (p.y = boxmin.y; p.y <= boxmax.y; p.y++)
			{
				Vec3f u = Barycentric(trianglePoints, Vec2i(p.x, p.y));
				//std::cout << u.x << " " << u.y << " " << u.z;
				if (u.x >= 0 && u.y >= 0 && u.z >= 0)
				{
					p.z = 0;
					p.z += a.z * u.x;
					p.z += b.z * u.y;
					p.z += c.z * u.z;
					if (zBuffer[int(p.x + p.y * height)] < p.z)
					{
						zBuffer[int(p.x + p.y * height)] = p.z;
						image.set(p.x, p.y, color);
					}
				}
			}
		}
	}
	void DrawModelByColor(Model* model, TGAImage& image, bool isRand = true, const TGAColor& color = TGAColor(255, 255, 255, 255))
	{
		for (int i = 0; i < model->nfaces(); i++) 
		{
			std::vector<int> face = model->face(i);
			//std::vector<Vec2i> screen_coords(3);
			std::vector<Vec3f> world_coords(3);
			for (int j = 0; j < 3; j++) 
			{
				world_coords[j] = model->vert(face[j]);
				//screen_coords[j] = Vec2i((world_coords.x + 1.) * width / 2., (world_coords.y + 1.) * height / 2.);
			}
			if (isRand)
				Traingle(world_coords, zBuffer,image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
			else
				Traingle(world_coords,zBuffer, image, color);
		}
	}
	void DrawModelWithLight(Model* model, TGAImage& image, Vec3f& lightdir, const TGAColor& lightColor = TGAColor(255, 255, 255, 255))
	{
		int r = lightColor.r;
		int b = lightColor.b;
		int g = lightColor.g;
		lightdir.normalize();
		for (int i = 0; i < model->nfaces(); i++)
		{
			std::vector<int> face = model->face(i);
			std::vector<Vec2i> screen_coords(3);
			std::vector<Vec3f> world_coords(3);
			for (int j = 0; j < 3; j++)
			{
				world_coords[j] = model->vert(face[j]);
				screen_coords[j] = Vec2i((world_coords[j].x + 1.) * width / 2., (world_coords[j].y + 1.) * height / 2.);
			}
			Vec3f normal = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
			normal.normalize();
			float intense = normal * lightdir;
			for (int j = 0; j < 3; j++)
				world_coords[j] = Vec3f(screen_coords[j].x, screen_coords[j].y, world_coords[j].z);
			if (intense > 0)
			{
				Traingle(world_coords,zBuffer, image, TGAColor(r * intense, g * intense, b * intense, 255));
			}
		}
	}
};

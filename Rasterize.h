#pragma once
#ifndef RASTERIZE_H_
#define RASTERIZE_H_
#endif 

#include "V2F.h"
#include "FrameBuffer.h"
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Rasterize
{
public:
	FrameBuffer FrontBuffer;
	Shader shader;
	int width;
	int height;
	std::vector<unsigned int>& colorBuffer = FrontBuffer.colorBuffer;
	Rasterize() :FrontBuffer(1920, 1080) 
	{
		FrontBuffer.ClearBuffer(glm::vec4(0, 255, 0, 0));	
		FrontBuffer.Resize(1920, 1080);
		width = 1920;
		height = 1080;
		colorBuffer = FrontBuffer.colorBuffer;
	};
	Rasterize(int width, int height) :FrontBuffer(width, height)
	{
		FrontBuffer.ClearBuffer(glm::vec4(0, 255, 0, 0));
		FrontBuffer.Resize(width, height);
		this->width = width;
		this->height = height;
		colorBuffer = FrontBuffer.colorBuffer;
	}
	~Rasterize()=default;

	void ScanTriangle(const V2F& v1, const V2F& v2, const V2F& v3);
	void UpTriangle(const V2F& v1, const V2F& v2, const V2F& v3);
	void DownTriangle(const V2F& v1, const V2F& v2, const V2F& v3);
	void ScanLine(const V2F& v1, const V2F& v2);
	void Sort(std::vector<V2F>& arr, int l, int r);
private:

};

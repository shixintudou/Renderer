#include "FrameBuffer.h"
void FrameBuffer::ClearBuffer(const glm::vec4& color)
{
	auto* p = colorBuffer.data();
	for (int i = 0; i < width * height * 4; i += 4)
	{
		*(p + i) = color.r;
		*(p + i + 1) = color.g;
		*(p + i + 2) = color.b;
		*(p + i + 3) = color.a;
	}
}

void FrameBuffer::WritePoint(const int& x, const int& y, const glm::vec4& color)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;
	int xy = y * width + x;
	colorBuffer[xy] = color.r;
	colorBuffer[xy + 1] = color.g;
	colorBuffer[xy + 2] = color.b;
	colorBuffer[xy + 3] = color.a;
}
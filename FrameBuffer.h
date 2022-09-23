#pragma once
#include <vector>
#include <glm/glm/glm.hpp>
class FrameBuffer
{
public:
	FrameBuffer() = default;
	~FrameBuffer() = default;

	int width = 1920;
	int height = 1080;
	std::vector<unsigned char> colorBuffer;
	FrameBuffer(int wid, int hei) :width(wid), height(hei) 
	{
		colorBuffer.resize(wid * hei * 4);
	};
	void Resize(int wid, int hei)
	{
		width = wid;
		height = hei;
		colorBuffer.resize(wid * hei * 4);
	}
	void ClearBuffer(const glm::vec4& color);
	void WritePoint(const int& x, const int& y, const glm::vec4& color);
private:

};




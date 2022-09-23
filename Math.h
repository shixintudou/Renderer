#pragma once
#include <glm/glm/glm.hpp>
class Math
{
public:
	Math()=default;
	~Math()=default;
	template <typename T>
	static T Lerp(const T& v1, const T& v2, float factor)
	{
		return (1.0f - factor) * v1 + factor * v2;
	}
	static glm::mat4 GetViewPortMatrix(int ox, int oy, int width, int height)
	{
		glm::mat4 result = glm::mat4(1.0f);
		result[0][0] = width / 2.0f;
		result[3][0] = ox + (width / 2.0f);
		result[1][1] = height / 2.0f;
		result[3][1] = oy + (height / 2.0f);
		return result;
	}
private:

};

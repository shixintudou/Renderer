#pragma once
#include<glm/glm/glm.hpp>
#include "Math.h"
class V2F
{
public:
	V2F()=default;
	~V2F()=default;

	glm::vec4 worldPos;
	glm::vec4 windowPos;
	glm::vec2 texcoord;
	glm::vec3 normal;
	glm::vec4 color;

	V2F(const glm::vec4& _worldPos, const glm::vec4& _windowPos, const glm::vec2& _texcoord, const glm::vec3& _normal, const glm::vec4& _color)
	{
		worldPos = _worldPos;
		windowPos = _windowPos;
		texcoord = _texcoord;
		normal = _normal;
		color = _color;
	}
	V2F(const V2F& v2f)
	{
		worldPos = v2f.worldPos;
		windowPos = v2f.windowPos;
		texcoord = v2f.texcoord;
		normal = v2f.normal;
		color = v2f.color;
	}
	static V2F Lerp(const V2F& v1, const V2F& v2, const float& factor)
	{
		V2F result;
		result.worldPos = Math::Lerp<glm::vec4>(v1.worldPos, v2.worldPos, factor);
		result.windowPos = Math::Lerp<glm::vec4>(v1.windowPos, v2.windowPos, factor);
		result.texcoord = Math::Lerp<glm::vec2>(v1.texcoord, v2.texcoord, factor);
		result.normal = Math::Lerp<glm::vec3>(v1.normal, v2.normal, factor);
		result.color = Math::Lerp<glm::vec4>(v1.color, v2.color, factor);
		return result;
	}
};

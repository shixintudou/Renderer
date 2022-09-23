#pragma once
#include <glm/glm/glm.hpp>
class Vertex
{
public:
	Vertex() = default;
	~Vertex() = default;

	glm::vec4 position;
	glm::vec2 texcoord;
	glm::vec4 color;
	glm::vec3 normal;

	Vertex(const glm::vec4& pos, const glm::vec2& tex, const glm::vec4& col, const glm::vec3& nor)
	{
		position = pos;
		texcoord = tex;
		color = col;
		normal = nor;
	}
	Vertex(
		const glm::vec3& _pos,
		const glm::vec4& _color = glm::vec4(0, 0, 0, 0),
		const glm::vec2& _tex = glm::vec2(0, 0),
		const glm::vec3& _normal = glm::vec3(0, 0, 1)
	) :
		position(_pos, 1.0f), color(_color), texcoord(_tex), normal(_normal) {}
	Vertex(const Vertex& vertex)
	{
		position = vertex.position;
		color = vertex.color;
		texcoord = vertex.texcoord;
		normal = vertex.normal;
	}
};
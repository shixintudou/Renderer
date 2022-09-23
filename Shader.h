#pragma once
#include <glm/glm/glm.hpp>
#include "V2F.h"
#include "Vertex.h"
class Shader
{
public:
	Shader()
	{
		modelMatrix = glm::mat4(1.0f);
		viewMatrix = glm::mat4(1.0f);
		projectMatrix = glm::mat4(1.0f);
	}
	~Shader()=default;

	
private:
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectMatrix;

public:
	V2F VertexShader(const Vertex& a2v)
	{
		V2F v2f;
		v2f.worldPos = modelMatrix * a2v.position;
		v2f.windowPos = projectMatrix * viewMatrix * v2f.worldPos;
		v2f.color = a2v.color;
		v2f.normal = a2v.normal;
		v2f.texcoord = a2v.texcoord;
		return v2f;
	}

	glm::vec4 FragmentShader(const V2F& v2f)
	{
		return v2f.color;
	}
	void SetModelMatrix(const glm::mat4& model)
	{
		modelMatrix = model;
	}
	void SetViewMatrix(const glm::mat4& view)
	{
		viewMatrix = view;
	}
	void SetProjectMatrix(const glm::mat4& project)
	{
		projectMatrix = project;
	}
};

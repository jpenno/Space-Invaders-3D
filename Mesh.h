#pragma once
#include <vector>
#include <glm/glm.hpp>


class Vertex
{
public:
	glm::vec4 pos;
	glm::vec4 col;
	glm::vec2 uv;
	glm::vec3 normal;

	static void SetupVertexAttribPointers();
};
class Mesh
{
protected:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;

	std::vector<unsigned short> m_indices;
	unsigned int m_numIndices;

public:
	Mesh();
	virtual ~Mesh();

	virtual void Make() = 0;
	virtual void Draw();
	virtual void Destory() = 0;
};

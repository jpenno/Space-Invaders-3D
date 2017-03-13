#pragma once
#include <vector>
#include "tiny_obj_loader.h"

#include <glm/mat4x4.hpp>

class OBJ
{
private:
	struct OBJVertex { 
		float x, y, z;
		float nx, ny, nz; 
		float u, v; 
	};

	struct GLInfo {
		unsigned int vao;
		unsigned int vbo1;
		unsigned int vbo2;
		unsigned int faceCount; 
	};

	std::vector<GLInfo> m_meshes;

	unsigned int m_shader = 0;
	float i = 0.0f;

public:
	OBJ();
	~OBJ();
	unsigned int createVertexBuffer(const tinyobj::attrib_t& attribs, const tinyobj::shape_t& shape);

	void Make();
	void UpDate(float a_deltaTime);
	void Draw(glm::mat4 a_projMat, glm::mat4 a_viewMat);
};


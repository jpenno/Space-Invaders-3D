#define GLM_SWIZZLE

#include "PlaneMesh.h"

#include "gl_core_4_4.h"
#include <glm/glm.hpp>

PlaneMesh::PlaneMesh()
{
}

PlaneMesh::~PlaneMesh()
{
}

void PlaneMesh::Make()
{
	int xDiv = 100;
	int zDiv = 100;

	std::vector<Vertex> verts;
	std::vector<unsigned short> indices;

	// build the height map
	for (int z = 0; z < zDiv; z++)
	{
		for (int x = 0; x < xDiv; x++)
		{
			unsigned int i = (z * xDiv + x);

			// get the value of the r component at the pixel located at x,z
			// the value returned is between 0 and 255 divided by 255 for a value between 0 and 1
			// mince 0.5 so we have a value between -0.5 and +0.5
			// multiply by 2 for a value between -1 and 1

			// position of vertex
			float xPos = (x*0.1f) - (xDiv*0.1f*0.5f);
			float yPos = 0;
			float zPos = (z*0.1f) - (zDiv*0.1f*0.5f);

			Vertex vert{
				{ xPos, yPos, zPos, 1.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				{ (float)x / (xDiv - 1), (float)z / (zDiv - 1) },
				{ 0, 0, 0 }
			};

			verts.push_back(vert);
		}
	}

	// calculate indices
	for (unsigned int z = 0; z < zDiv - 1; z++)
	{
		for (unsigned int x = 0; x < xDiv - 1; x++)
		{
			unsigned int i = z * xDiv + x;

			indices.push_back(i + 1);		// 1--0
			indices.push_back(i);			// | /
			indices.push_back(i + xDiv);	// 2

			indices.push_back(i + 1);			//    0
			indices.push_back(i + xDiv);		//  / |
			indices.push_back(i + xDiv + 1);	// 2--1
		}
	}

	for (int i = 0; i < indices.size() / 3; i++)
	{
		int index1 = indices[i * 3];
		int index2 = indices[i * 3 + 1];
		int index3 = indices[i * 3 + 2];

		glm::vec4 side1 = verts[index1].pos - verts[index3].pos;
		glm::vec4 side2 = verts[index1].pos - verts[index2].pos;

		glm::vec3 normal = glm::cross(side1.xyz(), side2.xyz());

		verts[index1].normal += normal;
		verts[index2].normal += normal;
		verts[index3].normal += normal;
	}

	for (int i = 0; i < verts.size(); i++)
	{
		verts[i].normal = glm::normalize(verts[i].normal);
	}

	m_indices = indices;

	//m_numIndices = indices.size();

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	// populate the buffers with the verts passed in
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verts.size(), &verts[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), &indices[0], GL_STATIC_DRAW);

	Vertex::SetupVertexAttribPointers();

	// un-bind the buffers;
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void PlaneMesh::Destory()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
	glDeleteVertexArrays(1, &m_vao);
}


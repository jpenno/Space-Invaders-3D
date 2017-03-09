#include "BoxMesh.h"
#include "gl_core_4_4.h"
#include <glm/glm.hpp>



void BoxMesh::SetVerts()
{
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
	// Step 1:
	// Specify the position and color for each vert of a cube
	// for this example, each face does not share a vert, so we have 4 verts for each face of our cube/


	Vertex verts[] = {
		// POSITION					COLOR
		// FRONT FACE				  
		{ { -0.5f,-0.5f, 0.5f, 1.0f }, color,{ 0.0f, 0.0f },{ 0.0f, 0.0f, -1.0f } },// 0
		{ {  0.5f,-0.5f, 0.5f, 1.0f }, color,{ 1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f } },// 1
		{ {  0.5f, 0.5f, 0.5f, 1.0f }, color,{ 1.0f, 1.0f },{ 0.0f, 0.0f, -1.0f } },// 2
		{ { -0.5f, 0.5f, 0.5f, 1.0f }, color,{ 0.0f, 1.0f },{ 0.0f, 0.0f, -1.0f } },// 3

		// BACK FACE				    			    
		{ { -0.5f,-0.5f,-0.5f, 1.0f }, color,{ 0.0f, 0.0f },{ 0.0f, 0.0f, 1.0f } },// 4
		{ {  0.5f,-0.5f,-0.5f, 1.0f }, color,{ 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0f } },// 5
		{ {  0.5f, 0.5f,-0.5f, 1.0f }, color,{ 1.0f, 1.0f },{ 0.0f, 0.0f, 1.0f } },// 6
		{ { -0.5f, 0.5f,-0.5f, 1.0f }, color,{ 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f } },// 7

		// LEFT FACE					    			    
		{ { -0.5f,-0.5f,-0.5f, 1.0f }, color,{ 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } },	// 8
		{ { -0.5f,-0.5f, 0.5f, 1.0f }, color,{ 0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f } },	// 9
		{ { -0.5f, 0.5f, 0.5f, 1.0f }, color,{ 1.0f, 1.0f },{ 1.0f, 0.0f, 0.0f } },	// 10
		{ { -0.5f, 0.5f,-0.5f, 1.0f }, color,{ 1.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } },	// 11

		// RIGHT FACE				
		{ { 0.5f,-0.5f,-0.5f, 1.0f }, color,{ 0.0f, 0.0f },{ -1.0f, 0.0f, 0.0f } },// 12
		{ { 0.5f,-0.5f, 0.5f, 1.0f }, color,{ 0.0f, 1.0f },{ -1.0f, 0.0f, 0.0f } },// 13
		{ { 0.5f, 0.5f, 0.5f, 1.0f }, color,{ 1.0f, 1.0f },{ -1.0f, 0.0f, 0.0f } },// 14
		{ { 0.5f, 0.5f,-0.5f, 1.0f }, color,{ 1.0f, 0.0f },{ -1.0f, 0.0f, 0.0f } },// 15

		// TOP FACE					  
		{ { -0.5f, 0.5f,-0.5f, 1.0f }, color,{ 0.0f, 0.0f },{ 0.0f, -1.0f, 0.0f } },// 16
		{ { -0.5f, 0.5f, 0.5f, 1.0f }, color,{ 0.0f, 1.0f },{ 0.0f, -1.0f, 0.0f } },// 17
		{ {  0.5f, 0.5f, 0.5f, 1.0f }, color,{ 1.0f, 1.0f },{ 0.0f, -1.0f, 0.0f } },// 18
		{ {  0.5f, 0.5f,-0.5f, 1.0f }, color,{ 1.0f, 0.0f },{ 0.0f, -1.0f, 0.0f } },// 19

		// BOTTOM FACE							    
		{ { -0.5f,-0.5f,-0.5f, 1.0f }, color,{ 0.0f, 0.0f },{ 0.0f, 1.0f, 0.0f } },	// 20
		{ { -0.5f,-0.5f, 0.5f, 1.0f }, color,{ 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f } },	// 21
		{ {  0.5f,-0.5f, 0.5f, 1.0f }, color,{ 1.0f, 1.0f },{ 0.0f, 1.0f, 0.0f } },	// 22
		{ {  0.5f,-0.5f,-0.5f, 1.0f }, color,{ 1.0f, 0.0f },{ 0.0f, 1.0f, 0.0f } }	// 23
	};

	m_verts.assign(verts, std::end(verts));
}

void BoxMesh::SetIndices()
{
	// Step 2:
	// From the above verts, we need to construct triangles that opengl can then use to render.
	// Winding order is important, each triangle needs to be described in a clockwise order
	// this defines the facing direction for the triangle.
	// By default OpenGL will cull pixels that are "facing away" from the camera glCullMode(GL_BACK) is the default setting.
	// Culling can be changed to GL_FRONT or GL_FRONT_AND_BACK, or enabled/disabled via glEnable(GL_CULL_FACE) / glDisable(GL_CULL_FACE)
	unsigned short indices[] =
	{
		0, 1, 2,	 0, 2, 3,  // front face
		6, 5, 4,	 7, 6, 4,  // back face
		8, 9, 10,	 8,10,11,  // left face
		14,13,12,	 15,14,12, // right face
		16,17,18,	 16,18,19, // top face
		22,21,20,	 23,22,20  // bottom face
	};

	m_indices.assign(indices, std::end(indices));
}

void BoxMesh::BindVboIbo()
{
	// Step 4:
	// Generate the VAO and Bind bind it.
	// Our VBO (vertex buffer object) and IBO (Index Buffer Object) will be "grouped" with this VAO
	// other settings will also be grouped with the VAO. this is used so we can reduce draw calls in the render method.
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Step 5:
	// Create our VBO and IBO.
	// Then tell Opengl what type of buffer they are used for
	// VBO a buffer in graphics memory to contains our vertices
	// IBO a buffer in graphics memory to contain our indices.
	// Then Fill the buffers with our generated data.
	// This is taking our verts and indices from ram, and sending them to the graphics card
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertex) * m_verts.size(), 
		&m_verts[0],
		GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
		sizeof(unsigned short) * m_indices.size(),
		&m_indices[0], 
		GL_STATIC_DRAW);

	// Step 6:
	// Vertices can have any shape, for us, each vertex has a position and color.
	// The "shape" of our vertex need to be described to OepnGL
	// This is so the vertices can be sent to our shader and be mapped to the correct variables locations.
	Vertex::SetupVertexAttribPointers();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

BoxMesh::BoxMesh()
{
}

BoxMesh::~BoxMesh()
{
}

void BoxMesh::Make()
{
	SetVerts();
	SetIndices();
	BindVboIbo();
}

void BoxMesh::Destory()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
	glDeleteVertexArrays(1, &m_vao);
}

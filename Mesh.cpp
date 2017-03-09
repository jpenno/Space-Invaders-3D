#include "Mesh.h"
#include "gl_core_4_4.h"


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::Draw()
{
	// Step 2: Bind the VAO
	// When we setup the geometry, we did a bunch of glEnableVertexAttribArray and glVertexAttribPointer method calls
	// we also Bound the vertex array and index array via the glBindBuffer call.
	// if we where not using VAO's we would have to do those method calls each frame here.
	glBindVertexArray(m_vao);

	// Step 3: Draw Elements. We are using GL_TRIANGLES.
	// we need to tell openGL how many indices there are, and the size of our indices
	// when we setup the geometry, our indices where an unsigned char (1 byte for each indicy)
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
}

void Vertex::SetupVertexAttribPointers()
{
	// enable vertex position element
	// notice when we loaded the shader, we described the "position" element to be location 0.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0 (position)
		4,                  // size - how many floats make up the position (x, y, z, w)
		GL_FLOAT,           // type - our x,y,z, w are float values
		GL_FALSE,           // normalized? - not used
		sizeof(Vertex),     // stride - size of an entire vertex
		(void*)0            // offset - bytes from the beginning of the vertex
	);

	// enable vertex color element
	// notice when we loaded the shader, we described the "color" element to be location 1.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute 1 (color)
		4,                  // size - how many floats make up the color (r, g, b, a)
		GL_FLOAT,           // type - our r,g,b,a are float values
		GL_FALSE,           // normalized? - not used
		sizeof(Vertex),     // stride - size of an entire vertex
		(void*)(sizeof(float) * 4)            // offset - bytes from the beginning of the vertex
	);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,                  // attribute 1 (uv)
		2,                  // size - how many floats make up the uv cords
		GL_FLOAT,           // type - our u,v are float values
		GL_FALSE,           // normalized? - not used
		sizeof(Vertex),     // stride - size of an entire vertex
		(void*)(sizeof(float) * 8)            // offset - bytes from the beginning of the vertex
	);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,                  // attribute 1 (normal)
		3,                  // size - how many floats make up the uv cords
		GL_FLOAT,           // type - our u,v are float values
		GL_FALSE,           // normalized? - not used
		sizeof(Vertex),     // stride - size of an entire vertex
		(void*)(sizeof(float) * 10)            // offset - bytes from the beginning of the vertex
	);
}


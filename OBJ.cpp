#include "OBJ.h"
#include "gl_core_4_4.h"

#include <ctime>

OBJ::OBJ()
{
}

OBJ::~OBJ()
{
}

void OBJ::Make()
{
	std::string err; 
	tinyobj::attrib_t attribs[2]; 
	std::vector<tinyobj::shape_t> shapes[2]; 
	std::vector<tinyobj::material_t> materials[2];
	tinyobj::LoadObj(&attribs[0], &shapes[0], &materials[0], &err, 
		"./hand/hand_00.obj", "./hand/");

	tinyobj::LoadObj(&attribs[1], &shapes[1], &materials[1], &err, 
		"./hand/hand_37.obj", "./hand/");


	// loaded models have matching shape counts 
	for (int i = 0; i < shapes[0].size(); ++i) 
	{
		GLInfo gl; gl.vbo1 = createVertexBuffer(attribs[0], shapes[0][i]); 
		gl.vbo2 = createVertexBuffer(attribs[1], shapes[1][i]); 

		// shapes have matching face counts 
		gl.faceCount = shapes[0][i].mesh.num_face_vertices.size();
		glGenVertexArrays(1, &gl.vao);
		glBindVertexArray(gl.vao); 

		// bind first VBO 
		glBindBuffer(GL_ARRAY_BUFFER, gl.vbo1); 
		glEnableVertexAttribArray(0); 

		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), 0);
		glEnableVertexAttribArray(1); 

		// normal data 
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(OBJVertex), (void*)12);
		glEnableVertexAttribArray(2); 

		// texture data 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), (void*)24);

		// bind second VBO
		glBindBuffer(GL_ARRAY_BUFFER, gl.vbo2); glEnableVertexAttribArray(3); 

		// position 2 
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), 0); 
		glEnableVertexAttribArray(4); 

		// normal 2
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_TRUE, sizeof(OBJVertex), (void*)12); 
		glBindVertexArray(0);

		m_meshes.push_back(gl); 
	}

	// set up shader
	const char * vsSource = 
	"// VERTEX SHADER									  \n \
	#version 410										  \n \
	layout(location = 0) in vec3 Position;				  \n \
	layout(location = 1) in vec3 Normal;			      \n \
	layout(location = 2) in vec2 TexCoord;			      \n \
	// from VBO 2									      \n \
	layout(location = 3) in vec3 Position2;			      \n \
	layout(location = 4) in vec3 Normal2;			      \n \
	out vec3 vNormal;								      \n \
	out vec2 vTexCoord;								      \n \
	uniform mat4 projectionViewModel;				      \n \
	// interpolation value between [0,1]			      \n \
	uniform float keyTime;							      \n \
	void main() {									      \n \
		// lerp position and normals				      \n \
		vec3 p = mix(Position, Position2, keyTime);	      \n \
		vec3 n = mix(Normal, Normal2, keyTime);			  \n \
		vNormal = n;									  \n \
		vTexCoord = TexCoord;							  \n \
		gl_Position = projectionViewModel * vec4(p, 1);	  \n \
	}";

	const char* fsSource =
		"#version 410					\n \
		in vec4 vNormal;				\n \
		in vec2 vuv;					\n \
		out vec4 FragColor;				\n \
		void main() {					\n \
			FragColor =  vec4(1,1,1,1); \n \
		}";


	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);
	m_shader = glCreateProgram();
	glAttachShader(m_shader, vertexShader);
	glAttachShader(m_shader, fragmentShader);
	glLinkProgram(m_shader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void OBJ::UpDate(float a_deltaTime)
{
	i += 1 * a_deltaTime;
}

void OBJ::Draw(glm::mat4 a_projMat, glm::mat4 a_viewMat)
{
	float s = 1.0f;
	glm::mat4 model = glm::mat4(
		s, 0, 0, 0,
		0, s, 0, 0,
		0, 0, s, 0,
		0, 10, 0, 1
	);


	glm::mat4 modelViewProjection = a_projMat * a_viewMat * model;
	glUseProgram(m_shader);
	// send uniform variables, in this case the "projectionViewWorldMatrix"
	unsigned int mvpLoc = glGetUniformLocation(m_shader, "projectionViewModel");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &modelViewProjection[0][0]);

	// example cosine interpolation between [0,1]
	int loc = glGetUniformLocation(m_shader, "keyTime");
	glUniform1f(loc, cosf(i * 3) * 0.5f + 0.5f);

	for (auto& gl : m_meshes) 
	{
		glBindVertexArray(gl.vao);
		glDrawArrays(GL_TRIANGLES, 0, gl.faceCount * 3);
	}
}

unsigned int OBJ::createVertexBuffer(const tinyobj::attrib_t& attribs, const tinyobj::shape_t& shape)
{ 
	// collect triangle vertices 
	std::vector<OBJVertex> vertices; 
	int index = 0;
	for (auto face : shape.mesh.num_face_vertices) 
	{ 
		for (int i = 0; i < 3; ++i) 
		{ 
			tinyobj::index_t idx = shape.mesh.indices[index + i]; 
			OBJVertex v = { 0 };
			// positions
			v.x = attribs.vertices[3 * idx.vertex_index + 0];
			v.y = attribs.vertices[3 * idx.vertex_index + 1]; 
			v.z = attribs.vertices[3 * idx.vertex_index + 2]; 
			// normals 
			if (attribs.normals.size() > 0)
			{ 
				v.nx = attribs.normals[3 * idx.normal_index + 0]; 
				v.ny = attribs.normals[3 * idx.normal_index + 1];
				v.nz = attribs.normals[3 * idx.normal_index + 2]; 
			} 
			// texture coordinates 
			if (attribs.texcoords.size() > 0)
			{ 
				v.u = attribs.texcoords[2 * idx.texcoord_index + 0]; 
				v.v = attribs.texcoords[2 * idx.texcoord_index + 1]; 
			} 
			vertices.push_back(v); 
		} 
		index += face; 
	} 
	// bind vertex data 
	unsigned int buffer = 0; 
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer); 
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(OBJVertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return buffer;
}
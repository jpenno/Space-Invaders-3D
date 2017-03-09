#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Mesh;
class Shader;
namespace aie
{
	class Texture;
};

class Model
{
private:
	Mesh *m_meshReff;
	Shader *m_shader = nullptr;

	glm::mat4 m_position = glm::mat4{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		2,1,2,1
	};


	aie::Texture *texture = nullptr;
public:
	Model();
	~Model();

	glm::mat4 GetPosition() { return m_position; }
	void SetMesh(Mesh &a_mesh);
	void SetShader(Shader *a_shader);

	void SetPostion(glm::mat4 a_position);
	void SetScale(glm::vec3 a_scale);

	void Draw();

};


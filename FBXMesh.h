#pragma once
#include "Mesh.h"
#include "FBXFile.h"

class GLMesh
{
public:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
};

class FBXMesh : public Mesh
{
private:
	FBXFile	*m_myFbxModel;
	unsigned int m_shader;

public:
	FBXMesh();
	~FBXMesh();

	void LoadFBX(char* filePath);

	void Draw(glm::mat4 a_projectionMat, glm::mat4 a_viewmat);

	virtual void Make() override;

	virtual void Destory() override;
};


#pragma once
#include "Mesh.h"

class Vertex;

class BoxMesh : public Mesh
{
private:
	std::vector<Vertex> m_verts;

	void SetVerts();
	void SetIndices();
	void BindVboIbo();

public:
	BoxMesh();
	~BoxMesh();

	virtual void Make() override;

	virtual void Destory() override;
};


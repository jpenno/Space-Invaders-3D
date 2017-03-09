#pragma once
#include "Mesh.h"
class PlaneMesh : public Mesh
{
private:

public:
	PlaneMesh();
	~PlaneMesh();

	virtual void Make() override;
	virtual void Destory() override;
};


#pragma once
#include "Application.h"
#include "Camera.h"
#include <glm/mat4x4.hpp>

#include "BoxMesh.h"
#include "PlaneMesh.h"
#include "FBXMesh.h"
#include "Model.h"
#include "DiffuseShader.h"
#include "TextureShader.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

#include "OBJ.h"


class Space_Invaders_3DApp : public aie::Application {
public:

	Space_Invaders_3DApp();
	virtual ~Space_Invaders_3DApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	Camera m_camera;

	Player m_player;
	std::vector<Enemy> m_enemy;

	DiffuseShader m_dShader;
	TextureShader m_etShader;
	TextureShader m_ptShader;
	TextureShader m_gtShader;

	BoxMesh m_cube;
	PlaneMesh m_planeMesh;
	FBXMesh m_fbxMesh;

	Model m_plane;
	Model m_testing;



	// FBO
	unsigned int m_fbo;
	unsigned int m_fboTexture;
	unsigned int m_fboDepth;


	OBJ testing;
};
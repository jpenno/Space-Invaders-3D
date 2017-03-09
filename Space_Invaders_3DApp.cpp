#include "Space_Invaders_3DApp.h"
#include "gl_core_4_4.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Space_Invaders_3DApp::Space_Invaders_3DApp() {

}

Space_Invaders_3DApp::~Space_Invaders_3DApp() {

}

bool Space_Invaders_3DApp::startup() {
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialize gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// set the enemy shader
	m_etShader.LoadFromFile("./textured.vert", "./textured.frag");
	m_etShader.Set(*m_camera.GetViewMatrix(), *m_camera.GetProjectionMatrix());
	m_etShader.SetColro(glm::vec3(1, 0, 0));

	// set the player shader
	m_ptShader.LoadFromFile("./textured.vert", "./textured.frag");
	m_ptShader.Set(*m_camera.GetViewMatrix(), *m_camera.GetProjectionMatrix());
	m_ptShader.SetColro(glm::vec3(0, 1, 0));

	// set the ground shader
	m_gtShader.LoadFromFile("./textured.vert", "./textured.frag");
	m_gtShader.Set(*m_camera.GetViewMatrix(), *m_camera.GetProjectionMatrix());
	m_gtShader.SetColro(glm::vec3(1, 1, 1));
	m_gtShader.SetTextureHandel(&m_fboTexture);
	//m_plane.SetShader(&m_gtShader);


	m_cube.Make();
	m_planeMesh.Make();

	// set up the game stuff
	m_player.SetModel(&m_ptShader, &m_cube);

	// set plane
	m_plane.SetMesh(m_planeMesh);
	m_plane.SetShader(&m_gtShader);

	glm::mat4 position = glm::mat4{
		5,0,0,0,
		0,5,0,0,
		0,0,10,0,
		0, -1, 2, 1
	};
	m_plane.SetPostion(position);


	float width = 5;
	float heigt = 5;
	float spaceing = 2;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < heigt; j++)
		{
			Enemy enemy;
			enemy.m_position = glm::vec3(
				(i * spaceing) - (width* spaceing * 0.5f),
				1,
				(j * spaceing) + 3);

			enemy.SetModel(&m_etShader, &m_cube);
			m_enemy.push_back(enemy);
		}
	}

	// setup and bind a framebuffer
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	// create a texture and bind it
	glGenTextures(1, &m_fboTexture);
	glBindTexture(GL_TEXTURE_2D, m_fboTexture);

	// specify texture format for storage
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 512, 512);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// attach it to the framebuffer as the first colour attachment
	// the FBO MUST still be bound
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		m_fboTexture, 0);

	// while the FBO is still bound
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	// setup and bind a 24bit depth buffer as a render buffer
	glGenRenderbuffers(1, &m_fboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_fboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
		512, 512);

	// while the FBO is still bound
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER, m_fboDepth);


	return true;
}

void Space_Invaders_3DApp::shutdown() {

	Gizmos::destroy();

	m_cube.Destory();
	m_planeMesh.Destory();
}

void Space_Invaders_3DApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	// update camera position
	//m_camera.Update(deltaTime);
	m_player.UpDate(deltaTime);

	// up date the camera position relative to the player
	m_camera.SetPoition(m_player.m_position + m_player.m_CameraOffSet, m_player.m_position);
}

void Space_Invaders_3DApp::draw() {
	// wipe the screen to the background colour
	//clearScreen();

	// update perspective based on screen size
	m_camera.SetProjectionMatrix(glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f));
	
	// bind the FBO so that we can render to the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glViewport(0, 0, 512, 512);
	glClearColor(0.75f, 0.75f, 0.75f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_player.Draw();

	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i].Draw();
	}

	// unbind the FBO so that we can render to the back buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1280, 720);
	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_player.Draw();

	m_plane.Draw();

	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i].Draw();
	}

	Gizmos::draw(*m_camera.GetProjectionMatrix() * *m_camera.GetViewMatrix());
}
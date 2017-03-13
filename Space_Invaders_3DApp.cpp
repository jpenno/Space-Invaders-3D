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

using namespace std;

Space_Invaders_3DApp::Space_Invaders_3DApp() {

}

Space_Invaders_3DApp::~Space_Invaders_3DApp() {

}

bool Space_Invaders_3DApp::startup() {
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialize gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// set up render target
	m_reflectionRenderTarget.Make();

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
	m_gtShader.SetTextureHandel(m_reflectionRenderTarget.GetTexture());

	// make meshes
	m_cube.Make();
	m_planeMesh.Make();
	m_fbxMesh.Make();

	// set up the game stuff
	m_player.SetModel(&m_ptShader, &m_cube);

	// set plane
	m_plane.SetMesh(m_planeMesh);
	m_plane.SetShader(&m_gtShader);

	glm::mat4 position = glm::mat4{
		3,0,0,0,
		0,3,0,0,
		0,0,3,0,
		0, -1, 10, 1
	};
	m_plane.SetPostion(position);

	m_enemyManager.Spawn(5, 5, 2, &m_etShader, &m_cube);

	m_animation.Make();

	return true;
}

void Space_Invaders_3DApp::shutdown() {
	Gizmos::destroy();

	m_cube.Destory();
	m_planeMesh.Destory();
	m_fbxMesh.Destory();
	m_enemyManager.Delete();
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
	m_camera.Update(deltaTime);
	m_player.UpDate(deltaTime);

	// up date the camera position relative to the player
	//m_camera.SetPoition(m_player.m_position + m_player.m_CameraOffSet, m_player.m_position);

	m_animation.UpDate(deltaTime);
}

void Space_Invaders_3DApp::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_camera.SetProjectionMatrix(glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f));

	// make the reflection matrix
	glm::mat4 refMat = m_camera.GetViewMatrixCopy() * m_plane.GetPosition();
	m_camera.SetViewMatrix(refMat);

	m_reflectionRenderTarget.Use();

	m_plane.Draw();

	m_player.Draw();

	m_enemyManager.Draw();

	// unbind the FBO so that we can render to the back buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1280, 720);
	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//m_camera.SetPoition(m_player.m_position + m_player.m_CameraOffSet, m_player.m_position);

	m_player.Draw();

	m_plane.Draw();

	m_fbxMesh.Draw(glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f),
		m_camera.GetViewMatrixCopy());
	
	m_enemyManager.Draw();

	m_animation.Draw(*m_camera.GetProjectionMatrix(), m_camera.GetViewMatrixCopy());

	Gizmos::draw(*m_camera.GetProjectionMatrix() * *m_camera.GetViewMatrix());
}
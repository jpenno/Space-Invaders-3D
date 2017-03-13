#pragma once

class RenderTarget
{
private:
	// FBO
	unsigned int m_fbo = 0;
	unsigned int m_fboTexture = 0;
	unsigned int m_fboDepth = 0;


public:
	RenderTarget();
	~RenderTarget();

	unsigned int* GetTexture();

	void Make();

	void Use();
};
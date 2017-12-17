#pragma once

class CGLFramework;

class CScene
{
public:
	CScene();
	virtual ~CScene();

	virtual void Initialize(CGLFramework * pFramework);

	virtual void Run();

	virtual void DrawScene();

	virtual void Render();

	virtual void Reshape(int w, int h);

	virtual void Keyboard(unsigned char key, int x, int y);

	virtual void SpecialKeyboard(int key, int x, int y);

	virtual void Mouse(int button, int state, int x, int y);

	virtual void Motion(int x, int y);

	virtual void Timer(int frame_time);

protected:

	CGLFramework*	m_Framework	{ nullptr }	;
};


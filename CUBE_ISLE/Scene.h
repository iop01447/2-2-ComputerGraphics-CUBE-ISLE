#pragma once

class CWin32Framework;

class CScene
{
public:
	CScene();
	virtual ~CScene();

	virtual void Update(float fTimeElapsed);

	virtual void Draw(HDC hDC);

	virtual bool Keyboard(UINT message, WPARAM wParam, LPARAM lParam);

	virtual bool Mouse(UINT message, WPARAM wParam, LPARAM lParam);

	virtual bool SETCURSOR();

	virtual bool Initialize(CWin32Framework* pFramework, HWND hWnd);

	virtual void ReleaseObjects();


protected:

	CWin32Framework	*	m_Framework	{ nullptr }	;
	HWND				m_hWnd		{ nullptr }	;
};


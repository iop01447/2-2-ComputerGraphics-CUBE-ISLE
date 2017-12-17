#pragma once
#include "stdafx.h"
#include "Camera.h"
#include "SoundManager.h"
#include "Zakka.h"
#include "Key.h"
#include "CubeMap.h"
#include "Skybox.h"
#include "Fog.h"
#include "Light.h"
#include "Skybox_star.h"

class CGLFramework		// c의 의미: c++ 클래스다 / 구조체랑 구분
{
public:
	CGLFramework();
	~CGLFramework();

	void Initialize(int argc, char* argv[]
		, int width, int height, int x, int y, const char* caption
		, int DsplayMove = GLUT_DOUBLE | GLUT_RGBA);

	void Run();

	void DrawScene();

	void Render();

	void Reshape(int w, int h);

	void Keyboard(unsigned char key, int x, int y);

	void SpecialKeyboard(int key, int x, int y);

	void Mouse(int button, int state, int x, int y);

	void Motion(int x, int y);

	void Timer(int value);

	using DrawFunc = void(*)();
	using ReshapeFunc = void(*)(int, int);
	using TimerFunc = void(*)(int);	// C11
	using KeyboardFunc = void(*)(unsigned char, int, int);
	using SpecialKeyboardFunc = void(*)(int, int, int);
	using MouseFunc = void(*)(int, int, int, int);
	using MotionFunc = void(*)(int, int);

	void RegisterDrawFunction(DrawFunc draw) { fnDraw = draw; }
	void RegisterReshapeFunction(ReshapeFunc reshape) { fnReshape = reshape; }
	void RegisterTimerFunction(TimerFunc timer) { fnTimer = timer; }
	void RegisterKeyboardFunction(KeyboardFunc keyboard) { fnKeyboard = keyboard; }
	void RegisterSpecialKeyboardFunction(SpecialKeyboardFunc specialkeyboard) { fnSpecialKeyboard = specialkeyboard; }
	void RegisterMouseFunction(MouseFunc mouse) { fnMouse = mouse; }
	void RegisterMotionFunction(MotionFunc motion) { fnMotion = motion; }

	void Bind()
	{
		glutDisplayFunc(fnDraw);	// 출력 함수의 지정 // 람다 익명 함수 // C11
		glutReshapeFunc(fnReshape);
		glutTimerFunc(m_fps, fnTimer, 1);
		glutKeyboardFunc(fnKeyboard);
		glutSpecialFunc(fnSpecialKeyboard);
		glutMouseFunc(fnMouse);
		glutMotionFunc(fnMotion);
	}

private:

	DrawFunc			fnDraw{ nullptr };
	ReshapeFunc			fnReshape{ nullptr };
	TimerFunc			fnTimer{ nullptr };
	KeyboardFunc		fnKeyboard{ nullptr };
	SpecialKeyboardFunc	fnSpecialKeyboard{ nullptr };
	MouseFunc			fnMouse{ nullptr };
	MotionFunc			fnMotion{ nullptr };

	int					m_fps = 16;	// 60 frame

	//
	Vector2				mStart;
	Vector2				mEnd;
	bool				drag = false;

	Camera				camera;
	bool				is_fpv = false;	// 일인칭이냐?

	//  사운드 
	CSoundManager		m_soundmgr;

	//
	CubeMap				cubemap;
	Skybox				skybox;
	
	int					player_y_rot = 180;

	Fog					fog;

	Light				light;

	Star				star;
};

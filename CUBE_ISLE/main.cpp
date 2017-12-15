#include "stdafx.h"
#include "CGLFramework.h"

namespace
{	// 익명 네임스페이스 - 전역변수를 쓰지 않기 위한 방법 // C11
	CGLFramework framework;
}

void main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));

	framework.Initialize(argc, argv, WIDTH, HEIGHT, 100, 100, "CUBE_ISLE");

	framework.RegisterDrawFunction([]() {framework.DrawScene(); });
	framework.RegisterReshapeFunction([](int w, int h) {framework.Reshape(w, h); });
	framework.RegisterTimerFunction([](int val) {framework.Timer(val); });
	framework.RegisterKeyboardFunction([](unsigned char key, int x, int y) {framework.Keyboard(key, x, y); });
	framework.RegisterSpecialKeyboardFunction([](int key, int x, int y) {framework.SpecialKeyboard(key, x, y); });
	framework.RegisterMouseFunction([](int button, int state, int x, int y) {framework.Mouse(button, state, x, y); });
	framework.RegisterMotionFunction([](int x, int y) {framework.Motion(x, y); });

	framework.Bind();
	framework.Run();
}


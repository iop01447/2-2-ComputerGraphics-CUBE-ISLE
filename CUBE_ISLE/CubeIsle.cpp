#include "CubeIsle.h"
#include "CGLFramework.h"


CubeIsle::CubeIsle()
{
	// 사운드
	m_soundmgr.AddSound("BGM", "Sound/Refunct_Game_Ost.mp3", SoundType::Stream);
	PushPlayQueue("BGM", Vector3(0, 0, 0));
	m_soundmgr.AddSound("Warning", "Sound/Bomb_Timer_Sound_Effect.mp3", 700, 1000); // cube 크기 기준으로
	m_soundmgr.AddSound("GetKey", "Sound/Super Mario Bros - Coin Sound Effect.mp3", 700, 1000); // cube 크기 기준으로

	skybox.init();
}

CubeIsle::~CubeIsle()
{
}

void CubeIsle::DrawScene()
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLoadIdentity();

	Render();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glDisable(GL_FOG);
	light.light_off();
	glutSwapBuffers();
}

void CubeIsle::Render()
{
	glFrontFace(GL_CW);
	glEnable(GL_TEXTURE_2D);
	light.light_global();
	skybox.draw(camera.m_pos);
	glDisable(GL_TEXTURE_2D);
	glClear(GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CCW);
	star.draw(camera.m_pos, light.global_rot);
	glClear(GL_DEPTH_BUFFER_BIT);

	light.light_on();
	glEnable(GL_FOG);
	fog.draw();
	cubemap.draw();
}

void CubeIsle::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	camera.Initialize({ 0.f, 0.f, 0.f }, 610.f, 1.f, 1000.f, 60.f);
}

void CubeIsle::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'p' || key == 'P') {
		cubemap.Init();
		for (int i = 0; i < 7; ++i)
			light.pos_init(cubemap.key[i].pos, i);
	}
	else if (key == 'g' || key == 'G') {
		cubemap.is_draw_aabb = !cubemap.is_draw_aabb;
	}
	else if (key == 'q' || key == 'Q') { // 종료
		exit(0);
	}
	else if (key == 'i') { // 초기화

	}
	else if (key == '-') {
		camera.zoom(-10);
	}
	else if (key == '+') {
		camera.zoom(10);
	}
	else if (key == 't') {
		camera.Rotate(0, radian(10));
	}
	else if (key == 'T') {
		camera.Rotate(0, radian(-10));
	}
	else if (key == 'y') {
		camera.Rotate(radian(10), 0);
	}
	else if (key == 'Y') {
		camera.Rotate(radian(-10), 0);
	}
	else if (key == ' ') { // 제어점 추가
		cubemap.player.jump_active = true;
	}
	else if (key == '1') {
		is_fpv = true;
		cubemap.player.rot.y = player_y_rot;
	}
	else if (key == '3') {
		is_fpv = false;
		player_y_rot = 180;
		camera.Initialize();
	}
	else if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
		if (!is_fpv) return;
		if (cubemap.player.jump_active) cubemap.player.jump_key = key;
		cubemap.player.key = cubemap.player.back_key = key;
	}
	else if (key == 'u') {
		cubemap.is_unbeatable = !cubemap.is_unbeatable;
		if (cubemap.is_unbeatable) cout << "무적모드" << endl;
		else cout << "무적모드 해제" << endl;
	}
}

void CubeIsle::SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {
	}
	else if (key == GLUT_KEY_RIGHT) {
	}
	else if (key == GLUT_KEY_UP) {
	}
	else if (key == GLUT_KEY_DOWN) {
	}
}

void CubeIsle::Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		drag = true;
		mStart = { (float)x, (float)y };
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (!drag) return;
		drag = false;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{

	}
}

void CubeIsle::Motion(int x, int y)
{
	if (drag) {
		mEnd = { (float)x,(float)y };
		int yRot = -((int)(mEnd.x - mStart.x)) % 360;
		int xRot = ((int)(mEnd.y - mStart.y)) % 360;
		camera.Rotate(radian(yRot), radian(xRot));
		mStart = { (float)x,(float)y };

		// player 회전
		player_y_rot = (player_y_rot + yRot) % 360;
		if (!is_fpv) return;
		cubemap.player.rot.y = player_y_rot;
	}
}

void CubeIsle::Timer(int frame_time)
{
	if (is_fpv) {
		// pos at up
		Vector3 at = cubemap.player.pos;
		camera.SetFpvPosition(at);
	}

	// look up pos
	FMOD_System_Instance()->update(0.016, camera.GetLookVector(), camera.m_up, camera.m_pos);
	if (PlayQueueSize() > 0) // 이벤트 큐 패턴
	{
		auto info = PopPlayQueue();
		m_soundmgr.Play(info.first, info.second);
	}

	cubemap.update(frame_time, camera, is_fpv, m_soundmgr);
	for (int i = 0; i < 7; ++i)
	{
		if (cubemap.key[i].exsist == false)
			light.exist[i] = false;
		else if (cubemap.key[i].exsist == true)
		{
			light.exist[i] = true;
			light.pos_init(cubemap.key[i].pos, i);
		}
	}
	light.update();
	fog.update(light.r, light.g, light.b);
	if (star.exist)
		star.update();
}


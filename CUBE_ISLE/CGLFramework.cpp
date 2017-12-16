#include "CGLFramework.h"

CGLFramework::CGLFramework()
{
}

CGLFramework::~CGLFramework()
{
}

void CGLFramework::Initialize(int argc, char * argv[], int width, int height, int x, int y, const char * caption, int DsplayMove)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(DsplayMove);	// ���÷��� ��� ����
	glutInitWindowSize(width, height);		// ������ ũ��
	glutInitWindowPosition(x, y);	// ������ ��ġ����
	glutCreateWindow(caption);

	// ����
	m_soundmgr.AddSound("BGM", "Sound/RefunctGameOst.mp3", SoundType::Stream);
	PushPlayQueue("BGM", Vector3(0, 0, 0));
//	m_soundmgr.AddSound("Click", "Sound/Equip.wav", 700, 1000); // cube ũ�� ��������

	skybox.init();
	for(int i = 0; i < 7; ++i)
		light.init(cubemap.key[i].pos, i);
}

void CGLFramework::Run()
{
	glutMainLoop();
}

void CGLFramework::DrawScene()
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

void CGLFramework::Render()
{
	glFrontFace(GL_CW);
	glEnable(GL_TEXTURE_2D);
	skybox.draw(camera.m_pos);
	glDisable(GL_TEXTURE_2D);
	glClear(GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CCW);
	light.light_global();
	glClear(GL_DEPTH_BUFFER_BIT);

	glEnable(GL_FOG);
	fog.draw();
	cubemap.draw();
	light.light_on();
}

void CGLFramework::Reshape(int w, int h)
{
	// ����Ʈ ��ȯ ����: ��� ȭ�� ����
	glViewport(0, 0, w, h);

	//// ���� ��� ���� �缳��
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//// Ŭ���� ���� ���� (���� ����)
	//gluPerspective(60.0f, (float)w / (float)h, 1.0, 1000.0);
	//glTranslatef(0.0, 0.0, -610.f); // ���� ������ ȭ�� �������� �̵��Ͽ� �þ߸� Ȯ���Ѵ�.

	//								// �� �� ��� ���� �缳��
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//// ���� ��ȯ: ī�޶��� ��ġ ����
	//gluLookAt(0.0, 0.0, 0.0,	// ī�޶��� ��ġ
	//	0.0, 0.0, 1.0,			// ī�޶� �ٶ󺸴� ��
	//	0.0, 1.0, 0.0);			// ī�޶��� ����

	camera.Initialize({ 0.f, 0.f, 0.f }, 610.f, 1.f, 1000.f, 60.f);
}

void CGLFramework::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'p' || key == 'P') {
		cubemap.Init();
		for (int i = 0; i < 7; ++i)
			light.init(cubemap.key[i].pos, i);
	}
	else if (key == 'g' || key == 'G') {
		cubemap.is_draw_aabb = !cubemap.is_draw_aabb;
	}
	else if (key == 'q' || key == 'Q') { // ����
		exit(0);
	}
	else if (key == 'i') { // �ʱ�ȭ
//		is_fpv = false;
//		camera.Initialize();
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
	else if (key == ' ') { // ������ �߰�
		cubemap.player.jump_active = true;
		//	PushPlayQueue("Click", cube.cardinal.current_pts);
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

	glutPostRedisplay();					// ȭ�� �����
}

void CGLFramework::SpecialKeyboard(int key, int x, int y)
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

void CGLFramework::Mouse(int button, int state, int x, int y)
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

void CGLFramework::Motion(int x, int y)
{
	if (drag) {
		mEnd = { (float)x,(float)y };
		int yRot = -((int)(mEnd.x - mStart.x)) % 360;
		int xRot = ((int)(mEnd.y - mStart.y)) % 360;
		camera.Rotate(radian(yRot), radian(xRot));
		mStart = { (float)x,(float)y };

		// player ȸ��
		player_y_rot = (player_y_rot + yRot) % 360;
		if (!is_fpv) return;
		cubemap.player.rot.y = player_y_rot;
	}
}

void CGLFramework::Timer(int value)
{
	if (is_fpv) {
		// pos at up
		Vector3 at = cubemap.player.pos;
		camera.SetFpvPosition(at);
	}

	// look up pos
	FMOD_System_Instance()->update(0.016, camera.GetLookVector(), camera.m_up, camera.m_pos);
	if (PlayQueueSize() > 0) // �̺�Ʈ ť ����
	{
		auto info = PopPlayQueue();
		m_soundmgr.Play(info.first, info.second);
	}

	cubemap.update(camera, is_fpv);
	light.update();

	glutTimerFunc(m_fps, fnTimer, 1);
	glutPostRedisplay();
}

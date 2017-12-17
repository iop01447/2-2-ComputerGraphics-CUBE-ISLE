#include "CGLFramework.h"
#include "CubeIsle.h"

CGLFramework::CGLFramework()
{
}

CGLFramework::~CGLFramework()
{
}

void CGLFramework::Initialize(int argc, char * argv[], int width, int height, int x, int y, const char * caption, int DsplayMove)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(DsplayMove);	// 디스플레이 모드 설정
	glutInitWindowSize(width, height);		// 윈도우 크기
	glutInitWindowPosition(x, y);	// 윈도우 위치지정
	glutCreateWindow(caption);

	auto pCubeIsle = new CubeIsle{};								

	m_Scenes[m_nCurrentScene++] = pCubeIsle;
	m_pCurrentScene = pCubeIsle;

	current_time = glutGet(GLUT_ELAPSED_TIME);
}

void CGLFramework::Run()
{
	glutMainLoop();
}

void CGLFramework::DrawScene()
{
	if (m_pCurrentScene) m_pCurrentScene->DrawScene();
}

void CGLFramework::Render()
{
	if (m_pCurrentScene) m_pCurrentScene->DrawScene();
}

void CGLFramework::Reshape(int w, int h)
{
	if (m_pCurrentScene) m_pCurrentScene->Reshape(w, h);
}

void CGLFramework::Keyboard(unsigned char key, int x, int y)
{
	if (m_pCurrentScene) m_pCurrentScene->Keyboard(key, x, y);

	glutPostRedisplay();					// 화면 재출력
}

void CGLFramework::SpecialKeyboard(int key, int x, int y)
{
	if (m_pCurrentScene) m_pCurrentScene->SpecialKeyboard(key, x, y);
}

void CGLFramework::Mouse(int button, int state, int x, int y)
{
	if (m_pCurrentScene) m_pCurrentScene->Mouse(button, state, x, y);
}

void CGLFramework::Motion(int x, int y)
{
	if (m_pCurrentScene) m_pCurrentScene->Motion(x, y);
}

void CGLFramework::Timer(int value)
{
	frame_time = glutGet(GLUT_ELAPSED_TIME) - current_time;

	if (m_pCurrentScene) m_pCurrentScene->Timer(frame_time);

	current_time = glutGet(GLUT_ELAPSED_TIME);
	
	glutTimerFunc(m_fps, fnTimer, 1);
	glutPostRedisplay();
}

void CGLFramework::PopScene()
{
	auto pScene = m_Scenes[m_nCurrentScene];
	m_Scenes[m_nCurrentScene] = nullptr;
	m_pCurrentScene = m_Scenes[--m_nCurrentScene];
	m_pCurrentScene->Initialize(this);
	delete pScene;
}

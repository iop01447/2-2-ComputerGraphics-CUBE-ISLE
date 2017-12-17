#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::Initialize(CGLFramework * pFramework)
{
	m_Framework = pFramework;
}

void CScene::Run()
{
}

void CScene::DrawScene()
{
}

void CScene::Render()
{
}

void CScene::Reshape(int w, int h)
{
}

void CScene::Keyboard(unsigned char key, int x, int y)
{
}

void CScene::SpecialKeyboard(int key, int x, int y)
{
}

void CScene::Mouse(int button, int state, int x, int y)
{
}

void CScene::Motion(int x, int y)
{
}

void CScene::Timer(int frame_time)
{
}
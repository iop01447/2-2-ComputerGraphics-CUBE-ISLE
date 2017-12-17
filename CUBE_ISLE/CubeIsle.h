#pragma once
#include "Scene.h"
#include "Camera.h"
#include "SoundManager.h"
#include "Zakka.h"
#include "Key.h"
#include "CubeMap.h"
#include "Skybox.h"
#include "Fog.h"
#include "Light.h"
#include "SoundManager.h"

class CubeIsle :
	public CScene
{
public:
	CubeIsle();
	~CubeIsle();

	void DrawScene() override;

	void Render() override;

	void Reshape(int w, int h) override;

	void Keyboard(unsigned char key, int x, int y) override;

	void SpecialKeyboard(int key, int x, int y) override;

	void Mouse(int button, int state, int x, int y) override;

	void Motion(int x, int y) override;

	void Timer(int value) override;

private:
	
	//  사운드 
	CSoundManager		m_soundmgr;

	Vector2				mStart;
	Vector2				mEnd;
	bool				drag = false;

	Camera				camera;
	bool				is_fpv = false;	// 일인칭이냐?

	CubeMap				cubemap;
	Skybox				skybox;
	Fog					fog;
	Light				light;

	int					player_y_rot = 180;
	int					current_time;
	int					frame_time;
};


#pragma once
#include "stdafx.h"
#include "Camera.h"

class Zakka
{
public:
	Zakka();
	~Zakka();

	Vector3 pos;
	Vector3 scl;
	Vector3 rot;
	float size;
	int slices;
	Aabb aabb;
	bool jump = false;

	void Init();
	void Init_aabb();
	void Draw();
	void draw_aabb();
	void move(Camera& camera, unsigned char key);
	void move_back(Camera& camera, unsigned char key);
	void jump();
	void jump_back();
	void yRotate(Vector3& add, int angle);
	void update();
	void update_back();
};


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
	bool jump_active = false;
	unsigned char key, back_key;
	unsigned char jump_key;
	int get_key_num;

	void Init();
	void Init_aabb();
	void Draw();
	void draw_aabb();
	void move(int, Camera& camera);
	void move_back(int, Camera& camera);
	void jump();
	void yRotate(Vector3& add, int angle);
	void update();
	void update_back();
};


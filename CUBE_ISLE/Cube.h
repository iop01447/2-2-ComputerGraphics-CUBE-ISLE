#pragma once
#include "stdafx.h"

class Cube {
public:
	bool exsist;
	Vector3 color;
	Vector3 pos;
	int size;
	Aabb aabb;
	bool is_sea = false;
	bool ani = false;
	Vector3 ani_cube_pos[50];
	Vector3 ani_random_vector[50];
	int ani_time = 0;
	float ani_cube_size = 5;
	Vector3 ani_color;

	Cube() = default;
	~Cube() = default;

	void draw() {
		draw_ani();

		if (!exsist) return;

		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		if (is_sea)
			glColor4f(color.x, color.y, color.z, 0.8);
		else
			glColor3fv(&color);
		glutSolidCube(size);
		glPopMatrix();
	}

	void draw_ani() {
		// 애니 //
		if (!ani) return;

		glColor3fv(&ani_color);
		for (int i = 0; i < 50; i++) {
			glPushMatrix();
			glTranslatef(ani_cube_pos[i].x, ani_cube_pos[i].y, ani_cube_pos[i].z);
			glutSolidCube(ani_cube_size);
			glPopMatrix();
		}
	}

	void draw_aabb() {
		if (!exsist) return;

		aabb.draw();
	}

	void ani_update(int frame_time) {
		if (!ani) return;

		// 애니메이션
		float t = ani_time / (1000.f * 3.f);
		float cube_size = (1.f - t) * 5.f + t * 0;
		if (ani) {
			for (int i = 0; i < 50; i++) {
				ani_cube_pos[i] += ani_random_vector[i] * 0.1 * frame_time * 0.06;
			}
			ani_time += frame_time;
			ani_cube_size = cube_size;
			if (ani_time > 1000 * 3) { // 3초
				ani = false;
				ani_time = 0;
				ani_cube_size = 5;
			}
		}
	}

	void ani_initialize() {
		ani = true;
		ani_color = color;
		for (int i = 0; i < 50; i++) {
			ani_cube_pos[i] = pos + Vector3{ -10.f + rand() % 20, -10.f + rand() % 20, -10.f + rand() % 20 };
			ani_random_vector[i] = { -5.f + rand() % 10, -5.f + rand() % 10 ,-5.f + rand() % 10 };
		}
	}
};

#pragma once
#include "stdafx.h"

class Cube {
public:
	bool exsist;
	Vector3 color;
	Vector3 pos;
	int size;
	Aabb aabb;

	Cube() = default;
	~Cube() = default;

	void draw() {
		if (!exsist) return;

		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glColor3fv(&color);
		glutSolidCube(size);
		glPopMatrix();

		aabb.draw();
	}
};

#define MAP_SIZE 10

class CubeMap {
public:
	Cube map[MAP_SIZE][MAP_SIZE][MAP_SIZE];
	
	CubeMap() {
		Init();
	}
	~CubeMap() = default;

	void Init() {
		Vector3 key_color = { (128 + rand() % 127) / 255.f, (128 + rand() % 127) / 255.f, (128 + rand() % 127) / 255.f };
		float map_size = HEIGHT / 2;
		float size = map_size / MAP_SIZE;
		Vector3 start_pos = { -map_size / 2 + size/2, -map_size / 2 + size/2, map_size / 2 - size/2 };
		Vector3 pos = start_pos;

		for (int i = 0; i < MAP_SIZE; i++) {	// x
			for (int j = 0; j < MAP_SIZE; j++) {	// y
				for (int k = 0; k < MAP_SIZE; k++) {	// z
					map[i][j][k].exsist = rand() % 5 == 0 ? true : false;
					map[i][j][k].color = { clamp((key_color.x * 255) - 50 - rand() % 77, 0.f, 255.f) / 255.f,
						clamp((key_color.y * 255) - 50 - rand() % 77, 0.f, 255.f) / 255.f ,
						clamp((key_color.z * 255) - 50 - rand() % 77, 0.f, 255.f) / 255.f };
					map[i][j][k].pos = pos;
					map[i][j][k].size = size;
					map[i][j][k].aabb = { pos - size / 2, pos + size / 2 };
					pos.z -= size;
				}
				pos.z = start_pos.z;
				pos.y += size;
			}
			pos.y = start_pos.y;
			pos.x += size;
		}

		cout << "key color: " << key_color.x << " " << key_color.y << " " << key_color.z << endl;
		cout << "key À§Ä¡:" << endl;
		for (int key = 0; key < 7; key++) {
			int x = rand() % MAP_SIZE;
			int y = rand() % MAP_SIZE;
			int z = rand() % MAP_SIZE;
			while (map[x][y][z].color == key_color || !map[x][y][z].exsist) {
				x = rand() % MAP_SIZE;
				y = rand() % MAP_SIZE;
				z = rand() % MAP_SIZE;
			}
			map[x][y][z].color = key_color;
			cout << x << " " << y << " " << z << endl;
		}
		cout << endl;
	}

	void draw() {
		float map_size = HEIGHT / 2;
		float size = map_size / MAP_SIZE;

		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
				for (int k = 0; k < MAP_SIZE; k++) {
					map[i][j][k].draw();
				}
			}
		}
	}
};
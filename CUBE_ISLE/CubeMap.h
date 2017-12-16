#pragma once
#include "stdafx.h"
#include "Cube.h"
#include "Zakka.h"
#include "Key.h"
#include "Camera.h"

#define MAP_SIZE 20
#define Y_SIZE 3

class CubeMap {
public:
	Cube map[MAP_SIZE][Y_SIZE][MAP_SIZE];
	bool is_draw_aabb = false;
	Zakka player;
	Key key[7];

	CubeMap() {
		Init();
	}
	~CubeMap() = default;

	void Init() {
		// cubemap init //
		Vector3 key_color = Vector3{ 128.f + rand() % 127, 128.f + rand() % 127, 128.f + rand() % 127 }.color();
		float map_size = HEIGHT / 2;
		float size = map_size / MAP_SIZE;
		Vector3 start_pos = { -map_size / 2 + size / 2, -size*Y_SIZE + size / 2, map_size / 2 - size / 2 };
		Vector3 pos = start_pos;

		// map init
		for (int i = 0; i < MAP_SIZE; i++) {	// x
			for (int j = 0; j < Y_SIZE; j++) {	// y
				for (int k = 0; k < MAP_SIZE; k++) {	// z
					map[i][j][k].exsist = rand() % 3 == 0 ? true : false;
					map[i][j][k].color = Vector3{ clamp((key_color.x * 255) - 50 - rand() % 77, 0.f, 255.f) ,
						clamp((key_color.y * 255) - 50 - rand() % 77, 0.f, 255.f) ,
						clamp((key_color.z * 255) - 50 - rand() % 77, 0.f, 255.f) }.color();
					map[i][j][k].pos = pos;
					map[i][j][k].size = size;
					map[i][j][k].aabb = { pos - size / 2.f, pos + size / 2.f };
					// sea
					if (j == 0 && !map[i][j][k].exsist) {
						map[i][j][k].exsist = true;
						map[i][j][k].is_sea = true;
						map[i][j][k].color = Vector3{ 34.f,213.f,249.f }.color();
					}
					pos.z -= size;
				}
				pos.z = start_pos.z;
				pos.y += size;
			}
			pos.y = start_pos.y;
			pos.x += size;
		}

		// key init
		cout << "key color: " << key_color.x << " " << key_color.y << " " << key_color.z << endl;
		cout << "key cube 위치:" << endl;
		for (int i = 0; i < 7; i++) {
			int x = rand() % MAP_SIZE;
			int y = 1 + rand() % 2;
			int z = rand() % MAP_SIZE;
			while (map[x][y][z].color == key_color || !map[x][y][z].exsist) {
				x = rand() % MAP_SIZE;
				y = 1 + rand() % 2;
				z = rand() % MAP_SIZE;
			}
			map[x][y][z].color = key_color;
			if (y == 1) map[x][y + 1][z].exsist = false;
			key[i].pos = map[x][y][z].pos + Vector3{ 0, size, 0 };
			key[i].Init_aabb();
			cout << x << " " << y << " " << z << endl;
		}
		cout << endl;

		// player init
		player.pos = map[MAP_SIZE / 2][Y_SIZE - 1][MAP_SIZE / 2].pos + Vector3{0, size / 2 + player.scl.y, 0};
		player.Init_aabb();
		map[MAP_SIZE / 2][Y_SIZE - 1][MAP_SIZE / 2].exsist = true;
	}

	void draw() {
		float map_size = HEIGHT / 2;
		float size = map_size / MAP_SIZE;

		// map draw
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < Y_SIZE; j++) {
				for (int k = 0; k < MAP_SIZE; k++) {
					map[i][j][k].draw();
				}
			}
		}

		// player draw
		player.Draw();

		// key draw
		for (int i = 0; i < 7; i++)
			key[i].Draw();

		// aabb draw
		if (is_draw_aabb)
			draw_aabb();
	}
	void draw_aabb() {
		// map aabb
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < Y_SIZE; j++) {
				for (int k = 0; k < MAP_SIZE; k++) {
					map[i][j][k].draw_aabb();
				}
			}
		}

		// player aabb
		player.draw_aabb();

		// key aabb
		for (int i = 0; i < 7; i++)
			key[i].draw_aabb();
	}

	void update(Camera& camera, bool is_fpv) {
		for(int i=0; i<7; i++)
			key[i].Update();
		
		// 중력
		player.update();
		if (collide_check_player_map())
			player.update_back();

		// 이동
		if (!is_fpv) return;
		player.move(camera);
	//	player.key = 0;
		if (collide_check_player_map()) {
			player.move_back(camera);
			player.key = player.back_key = 0;
		}
		collide_check_player_key();
	}

	bool collide_check_player_map() {
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < Y_SIZE; j++) {
				for (int k = 0; k < MAP_SIZE; k++) {
					if (!map[i][j][k].exsist) continue;
					if (AabbAabbIntersection(player.aabb, map[i][j][k].aabb)) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool collide_check_player_key() {
		for (int i = 0; i < 7; i++) {
			if (!key[i].exsist) continue;
			if (AabbAabbIntersection(player.aabb, key[i].aabb)) {
				player.get_key_num++;
				key[i].exsist = false;
				return true;
			}
		}
		return false;
	}
};
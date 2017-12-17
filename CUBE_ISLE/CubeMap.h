#pragma once
#include "stdafx.h"
#include "Cube.h"
#include "Zakka.h"
#include "Key.h"
#include "Camera.h"
#include "SoundManager.h"

#define MAP_SIZE 20
#define Y_SIZE 3

class CubeMap {
public:
	Cube map[MAP_SIZE][Y_SIZE][MAP_SIZE];
	bool is_draw_aabb = false;
	Zakka player;
	Key key[7];
	int key_cube_index[7][3];
	bool is_unbeatable = true;
	Vector3 key_color;
	int player_cube[3]; // player가 위치한 큐브의 index
	int player_cube_total_frame_time = 0; // player가 똑같은 큐브 위에 얼마나 있었나
	bool warning = false;

	CubeMap() {
		Init();
	}
	~CubeMap() = default;

	void Init() {
		// cubemap init //
		key_color = Vector3{ 128.f + rand() % 127, 128.f + rand() % 127, 128.f + rand() % 127 }.color();
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
			key_cube_index[i][0] = x;
			key_cube_index[i][1] = y;
			key_cube_index[i][2] = z;
			if (y == 1) map[x][y + 1][z].exsist = false;
			key[i].pos = map[x][y][z].pos + Vector3{ 0, size, 0 };
			key[i].Init_aabb();
			key[i].exsist = true;
			cout << x << " " << y << " " << z << endl;
		}
		cout << endl;

		// player init
		player.pos = map[MAP_SIZE / 2][Y_SIZE - 1][MAP_SIZE / 2].pos + Vector3{0, size / 2 + player.scl.y, 0};
		player.Init_aabb();
		player.get_key_num = 0;
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

	void update(int frame_time, Camera& camera, bool is_fpv, CSoundManager& soundmanager) {
		// 키
		for(int i=0; i<7; i++)
			key[i].Update();
		
		// 중력 & 점프
		player.update();
		if (collide_check_player_map(soundmanager))
			player.update_back();
		if (player.pos.y < -100) {
			player_dead(false);
		}

		// 큐브 부시기
		player_cube_total_frame_time += frame_time;
		if (!warning && player_cube_total_frame_time > 1000 * 2) {
			warning = true;
			PushPlayQueue("Warning", map[player_cube[0]][player_cube[1]][player_cube[2]].pos);
			player_cube_total_frame_time = 0;
		}
		if (warning && player_cube_total_frame_time > 1000 * 6.7) {
			warning = false;
			int i = player_cube[0];
			int j = player_cube[1];
			int k = player_cube[2];

			if (!map[i][j][k].ani) {
				map[i][j][k].ani_initialize();
				if (j == 0) {
					map[i][j][k].is_sea = true;
					map[i][j][k].color = Vector3{ 34.f,213.f,249.f }.color();
				}
				else
					map[i][j][k].exsist = false;
			}
		}

		// 큐브 부쉬기 애니
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < Y_SIZE; j++) {
				for (int k = 0; k < MAP_SIZE; k++) {
					map[i][j][k].ani_update(frame_time);
				}
			}
		}

		// 이동
		if (!is_fpv) return;
		player.move(frame_time, camera);
	//	player.key = 0;
		if (collide_check_player_map(soundmanager)) {
			player.move_back(frame_time, camera);
			player.key = player.back_key = 0;
		}
		collide_check_player_key();
	}

	bool collide_check_player_map(CSoundManager& soundmanager) {
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < Y_SIZE; j++) {
				for (int k = 0; k < MAP_SIZE; k++) {
					if (!map[i][j][k].exsist) continue;
					if (AabbAabbIntersection(player.aabb, map[i][j][k].aabb)) {
						if (map[i][j][k].is_sea) {
							player_dead();
						}
						if (player_cube[0] != i || player_cube[1] != j || player_cube[2] != k) {
							player_cube_total_frame_time = 0;
							if(warning)
								soundmanager.Stop("Warning");
							warning = false;
						}
						player_cube[0] = i;
						player_cube[1] = j;
						player_cube[2] = k;
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
				map[key_cube_index[i][0]][key_cube_index[i][1]][key_cube_index[i][2]].color 
					= Vector3{ clamp((key_color.x * 255) - 50 - rand() % 77, 0.f, 255.f) ,
					clamp((key_color.y * 255) - 50 - rand() % 77, 0.f, 255.f) ,
					clamp((key_color.z * 255) - 50 - rand() % 77, 0.f, 255.f) }.color();
				if (player.get_key_num == 7) {
					HWND hwnd = GetForegroundWindow();
					if (MessageBox(hwnd,
						TEXT("Thank You ! \n새로운 게임을 플레이하시겠습니까?"),
						TEXT("게임 클리어"), MB_YESNO) == IDNO) {
						exit(0);
					}
					else {
						Init();
					}
				}
				return true;
			}
		}
		return false;
	}

	void player_dead(bool sea_dead = true) {
		if (is_unbeatable) {
			if (sea_dead) cout << "바다에 닿아서 ";
			else cout << "맵 밖으로 떨어져서 ";
			cout << "사망" << endl;
			return;
		}
		HWND hwnd = GetForegroundWindow();
		if (MessageBox(hwnd,
			TEXT("새로운 게임을 플레이하시겠습니까?"),
			TEXT("사망"), MB_YESNO) == IDNO) {
			exit(0);
		}
		else {
			Init();
		}
	}
};
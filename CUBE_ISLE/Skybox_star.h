#pragma once

#include "stdafx.h"
#define STARNUM		3000

class Star {
public:
	Star() {
		init();
	};
	~Star() = default;

	GLint DrawArea = 600;
	GLfloat r[STARNUM], g[STARNUM], b[STARNUM];
	Vector3 pos[STARNUM];
	GLboolean colorchange[STARNUM];
	GLfloat alpha[STARNUM];
	GLfloat space = 0;
	GLint star_cnt = 0;
	bool exist = false;

	void init() {
		for (int i = 0; i < STARNUM; ++i)
		{
			r[i] = (rand() % 100 + 70) / 100.0f;
			g[i] = (rand() % 100 + 70) / 100.0f;
			b[i] = (rand() % 100 + 70) / 100.0f;
			alpha[i] = (rand() % 100) / 100.0f;
			star_cnt = 0;

			//뒤
			if (i % 6 == 0)
			{
				pos[i].x = (rand() % DrawArea) - (DrawArea / 2);
				pos[i].y = (rand() % DrawArea) - (DrawArea / 2);
				pos[i].z = -DrawArea / 2;
			}
			//왼쪽
			else if (i % 6 == 1)
			{
				pos[i].x = -DrawArea / 2;
				pos[i].y = (rand() % DrawArea) - (DrawArea / 2);
				pos[i].z = (rand() % DrawArea) - (DrawArea / 2);
			}
			//앞
			else if (i % 6 == 2)
			{
				pos[i].x = (rand() % DrawArea) - (DrawArea / 2);
				pos[i].y = (rand() % DrawArea) - (DrawArea / 2);
				pos[i].z = DrawArea / 2;
			}
			//오른쪽
			else if (i % 6 == 3)
			{
				pos[i].x = DrawArea / 2;
				pos[i].y = (rand() % DrawArea) - (DrawArea / 2);
				pos[i].z = (rand() % DrawArea) - (DrawArea / 2);
			}
			//위쪽
			else if (i % 6 == 4)
			{
				pos[i].x = (rand() % DrawArea) - (DrawArea / 2);
				pos[i].y = DrawArea / 2;
				pos[i].z = (rand() % DrawArea) - (DrawArea / 2);
			}
			//아래쪽
			else if (i % 6 == 5)
			{
				pos[i].x = (rand() % DrawArea) - (DrawArea / 2);
				pos[i].y = -DrawArea / 2;
				pos[i].z = (rand() % DrawArea) - (DrawArea / 2);
			}
		}
	}

	void draw(Vector3& position, GLint light_rot) {
		if (0 <= light_rot && light_rot < 45)
		{
			for (int i = 0; i < STARNUM; ++i)
				alpha[i] -= (i % 10) / 100.0f;
		}
		else if (45 == light_rot)
			exist = false;
		else if (180 == light_rot)
		{
			exist = true;
			for (int i = 0; i < STARNUM; ++i)
				alpha[i] = (rand() % 100 + 20) / 100.0f;
		}
		else if (180 <= light_rot && light_rot < 225)
		{
			for (int i = 0; i < STARNUM; ++i)
				alpha[i] += (i % 10) / 100.0f;
		}

		if (exist)
		{
			glPushMatrix();
			glTranslatef(position.x, position.y, position.z);
			glPointSize(2);
			glBegin(GL_POINTS);
			for (int i = 0; i < STARNUM / 2; ++i)
			{
				glColor4f(r[i], g[i], b[i], alpha[i]);
				glVertex3f(pos[i].x, pos[i].y, pos[i].z);
			}
			glEnd();
			glPointSize(1);
			glBegin(GL_POINTS);
			for (int i = STARNUM / 2; i < STARNUM; ++i)
			{
				glColor4f(r[i], g[i], b[i], alpha[i]);
				glVertex3f(pos[i].x, pos[i].y, pos[i].z);
			}
			glEnd();
			glPopMatrix();
		}
	}

	void update() {
		star_cnt += 1;
		if (star_cnt > 2)
		{
			star_cnt = 0;
			for (int i = 0; i < STARNUM; ++i)
			{
				if (colorchange[i])
				{
					alpha[i] -= (i % 5) / 10.0f;
					if (alpha[i] <= 0.2f)
						colorchange[i] = false;
				}
				else if (!colorchange[i])
				{
					alpha[i] += (i % 10) / 100.0f;
					if (alpha[i] >= 1.0f)
					{
						colorchange[i] = true;
						r[i] = (rand() % 100 + 70) / 100.0f;
						g[i] = (rand() % 100 + 70) / 100.0f;
						b[i] = (rand() % 100 + 70) / 100.0f;
						alpha[i] = (rand() % 100 + 70) / 100.0f;
					}
				}
			}
		}
	}
};
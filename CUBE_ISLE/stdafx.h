// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include <stdlib.h>

/////////////////////////////////////////////////////
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#include <GL/glut.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <Windows.h>
//#include <cmath>
using namespace std;

#include "Vector2.h"
#include "Vector3.h"
#include "Aabb.h"

/////////////////////////////////////////////////////

#define WIDTH 1280
#define HEIGHT 720

#define PIE 3.141592653589
#define EPSILON 0.0001	// �ſ� ���� �Ǽ�

enum frame {
	circle, sine, tornado, zigzag, pathway
};
enum Shape {
	cone, cube, sphere, torus, teapot 
};

class Vector2;
/* STL vector�� �̿��ؼ� �ٰ��� �ڷ����� ���� �� */
typedef vector<Vector2> polygon;

///////////////////////////////////////////////////////////

// - �� a, b�� ������ ������ �� c, d�� ������ ������ ������ x�� ��ȯ�Ѵ�.
// - �� ������ �����̸�(��ġ�� ��� ����) ������, �ƴϸ� ���� ��ȯ�Ѵ�.
bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x);

bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2 & x);

double ccw(Vector2 a, Vector2 b);

double ccw(Vector2 p, Vector2 a, Vector2 b);

bool paralleSegments(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& p);

bool inBoundingRectangle(Vector2 p, Vector2 a, Vector2 b);

bool segmentIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& p);

bool sementIntersects(Vector2 a, Vector2 b, Vector2 c, Vector2 d);

void convertDeviceXYOpenGLXY(int x, int y, float* ox, float* oy);

bool isInside(Vector2 B, const polygon& p);

float fineTriangleArea(Vector2 p1, Vector2 p2, Vector2 p3);

float findPolygonArea(polygon& x);

void SetrandColor();

template <typename T>
T clamp(T x, T low, T high)
{
	assert(low <= high);
	return min(max(x, low), high);
}

// x = wrap(x, 0, 10)
// 0~9 ���θ� �� �����
// 10�̸� 0�� ��
int wrap(int x, int low, int high);
float wrap(float x, float low, float high);

bool AabbAabbIntersection(Aabb a, Aabb b);

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

float radian(int angle);
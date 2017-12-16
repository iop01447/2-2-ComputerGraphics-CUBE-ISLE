// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include <stdlib.h>

/////////////////////////////////////////////////////
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

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
#define EPSILON 0.0001	// 매우 작은 실수

enum frame {
	circle, sine, tornado, zigzag, pathway
};
enum Shape {
	cone, cube, sphere, torus, teapot 
};

class Vector2;
/* STL vector를 이용해서 다각형 자료형을 정의 함 */
typedef vector<Vector2> polygon;

///////////////////////////////////////////////////////////

// - 점 a, b를 지나는 직선과 점 c, d를 지나는 직선의 교점을 x에 반환한다.
// - 두 직선이 평행이면(겹치는 경우 포함) 거짓을, 아니면 참을 반환한다.
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
// 0~9 내부를 랩 어라운드
// 10이면 0이 됨
int wrap(int x, int low, int high);
float wrap(float x, float low, float high);

bool AabbAabbIntersection(Aabb a, Aabb b);

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

float radian(int angle);
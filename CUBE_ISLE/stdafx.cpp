// stdafx.c : 표준 포함 파일만 들어 있는 소스 파일입니다.
// main.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"
#include "Vector2.h"

// TODO: 필요한 추가 헤더는
// 이 파일이 아닌 STDAFX.H에서 참조합니다.

/////////////////////////////////////////////////////

// 직선과 직선의 교차점
bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2 & x)
{
	double det = (b - a).cross(d - c);
	//두선이 평행인 경우
	if (fabs(det) < EPSILON) return false; // fabs 부동소수점 절대값 리턴
	x = a + (b - a)*((c - a).cross(d - c) / det);
	return true;
}

//원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
double ccw(Vector2 a, Vector2 b) {
	return a.cross(b);
}

//점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
double ccw(Vector2 p, Vector2 a, Vector2 b) {
	return ccw(a - p, b - p);
}

//점 a, b와 점 c, d가 평행한 두 선분 일 때 이들이 한 점에서 겹치는지 확인한다.
bool paralleSegments(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& p) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);

	//한 직선위에 없거나 두 선분이 겹치지 않는 경우를 우선 걸러낸다. 본문의 1번 관계인 경우이다.
	if (ccw(a, b, c) != 0 || b < c || d < a) return false;

	//두 선분이 확실히 겹친다면 교차점 하나를 찾는다.
	if (a < c) p = c;
	else p = a;
	return true;
}

// - p가 두 점 a, b를 감싸면서 각 변이 x, y축에 평행한 최소사각형 내부에 있는지 확인한다.
// a, b, p는 일직선 상에 있다고 가정한다.
bool inBoundingRectangle(Vector2 p, Vector2 a, Vector2 b) {
	if (b < a) swap(a, b);
	return p == a || p == b || (a < p && p < b);
}

// - 두 점 a, b를 지나는 선분과 두 점 c, b를 지나는 선분의 교차점을 p에 반환한다.
// - 교짐이 여러개일 경우 아무점이나 반환한다.
bool segmentIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& p) {
	//두 직선이 평행인 경우를 우선 예외로 처리한다.
	if (!lineIntersection(a, b, c, d, p))
		return paralleSegments(a, b, c, d, p);
	//p가 두 선분에 포함되어 있는 경우에만 참을 반환한다.
	bool isture = inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);
	return isture;
}

//두 선분이 서로 접촉하는지 여부를 반환한다.
bool sementIntersects(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
	double ab = ccw(a, b, c)*ccw(a, b, d);
	double cd = ccw(c, d, a)*ccw(c, d, b);
	//두 선분이 한 직선에 위에 있거나 끝점이 겹치는 경우
	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

void convertDeviceXYOpenGLXY(int x, int y, float* ox, float* oy)
/* x,y : 윈도우 마우스 좌표 변수 , ox, oy : Open GL 좌표로 변환 후 저장할 변수 */
{
	float w = WIDTH;
	float h = HEIGHT;

	*ox = (float)(x - w / 2.0)*(1.0 / (w / 2.0));
	*oy = -(float)(y - h / 2.0)*(1.0 / (h / 2.0));
}

bool isInside(Vector2 B, const polygon & p)
{
	//crosses는 점q와 오른쪽 반직선과 다각형과의 교점의 개수
	int crosses = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		//점 B가 선분 (p[i], p[j])의 y좌표 사이에 있음
		if ((p[i].y > B.y) != (p[j].y > B.y)) {
			//atX는 점 B를 지나는 수평선과 선분 (p[i], p[j])의 교점
			double atX = (p[j].x - p[i].x)*(B.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			//atX가 오른쪽 반직선과의 교점이 맞으면 교점의 개수를 증가시킨다.
			if (B.x < atX)
				crosses++;
		}
	}
	return crosses % 2 > 0;
}

float fineTriangleArea(Vector2 p1, Vector2 p2, Vector2 p3)
{
	Vector2 a = p2 - p1;
	Vector2 b = p3 - p1;
	return fabs(a.cross(b)) / 2.f;
}

float findPolygonArea(polygon & x)
{
	float sum = 0;
	int i = 0;
	int j = 1;
	int k = 2;
	while (k < x.size()) {
		sum += fineTriangleArea(x[i], x[j++], x[k++]);
	}
	return sum;
}

void SetrandColor()
{
	glColor3f(rand() % 255 / 255.f, rand() % 255 / 255.f, rand() % 255 / 255.f);
}

int wrap(int x, int low, int high)
{
	assert(low < high);
	const int n = (x - low) % (high - low);
	return (n >= 0) ? (n + low) : (n + high);
}
float wrap(float x, float low, float high)
{
	assert(low < high);
	const float n = fmod(x - low, high - low);
	return (n >= 0) ? (n + low) : (n + high);
}

bool AabbAabbIntersection(Aabb a, Aabb b)
{
	if (a.max_.x < b.min_.x || a.min_.x > b.max_.x) return false;
	if (a.max_.y < b.min_.y || a.min_.y > b.max_.y) return false;
	if (a.max_.z < b.min_.z || a.min_.z > b.max_.z) return false;
	return true;
}

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 갂다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

float radian(int angle)
{
	return angle*PIE / 180.f;
}
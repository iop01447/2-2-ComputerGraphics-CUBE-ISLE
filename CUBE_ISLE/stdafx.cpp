// stdafx.c : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// main.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"
#include "Vector2.h"

// TODO: �ʿ��� �߰� �����
// �� ������ �ƴ� STDAFX.H���� �����մϴ�.

/////////////////////////////////////////////////////

// ������ ������ ������
bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2 & x)
{
	double det = (b - a).cross(d - c);
	//�μ��� ������ ���
	if (fabs(det) < EPSILON) return false; // fabs �ε��Ҽ��� ���밪 ����
	x = a + (b - a)*((c - a).cross(d - c) / det);
	return true;
}

//�������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
double ccw(Vector2 a, Vector2 b) {
	return a.cross(b);
}

//�� p�� �������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
double ccw(Vector2 p, Vector2 a, Vector2 b) {
	return ccw(a - p, b - p);
}

//�� a, b�� �� c, d�� ������ �� ���� �� �� �̵��� �� ������ ��ġ���� Ȯ���Ѵ�.
bool paralleSegments(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& p) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);

	//�� �������� ���ų� �� ������ ��ġ�� �ʴ� ��츦 �켱 �ɷ�����. ������ 1�� ������ ����̴�.
	if (ccw(a, b, c) != 0 || b < c || d < a) return false;

	//�� ������ Ȯ���� ��ģ�ٸ� ������ �ϳ��� ã�´�.
	if (a < c) p = c;
	else p = a;
	return true;
}

// - p�� �� �� a, b�� ���θ鼭 �� ���� x, y�࿡ ������ �ּһ簢�� ���ο� �ִ��� Ȯ���Ѵ�.
// a, b, p�� ������ �� �ִٰ� �����Ѵ�.
bool inBoundingRectangle(Vector2 p, Vector2 a, Vector2 b) {
	if (b < a) swap(a, b);
	return p == a || p == b || (a < p && p < b);
}

// - �� �� a, b�� ������ ���а� �� �� c, b�� ������ ������ �������� p�� ��ȯ�Ѵ�.
// - ������ �������� ��� �ƹ����̳� ��ȯ�Ѵ�.
bool segmentIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& p) {
	//�� ������ ������ ��츦 �켱 ���ܷ� ó���Ѵ�.
	if (!lineIntersection(a, b, c, d, p))
		return paralleSegments(a, b, c, d, p);
	//p�� �� ���п� ���ԵǾ� �ִ� ��쿡�� ���� ��ȯ�Ѵ�.
	bool isture = inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);
	return isture;
}

//�� ������ ���� �����ϴ��� ���θ� ��ȯ�Ѵ�.
bool sementIntersects(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
	double ab = ccw(a, b, c)*ccw(a, b, d);
	double cd = ccw(c, d, a)*ccw(c, d, b);
	//�� ������ �� ������ ���� �ְų� ������ ��ġ�� ���
	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

void convertDeviceXYOpenGLXY(int x, int y, float* ox, float* oy)
/* x,y : ������ ���콺 ��ǥ ���� , ox, oy : Open GL ��ǥ�� ��ȯ �� ������ ���� */
{
	float w = WIDTH;
	float h = HEIGHT;

	*ox = (float)(x - w / 2.0)*(1.0 / (w / 2.0));
	*oy = -(float)(y - h / 2.0)*(1.0 / (h / 2.0));
}

bool isInside(Vector2 B, const polygon & p)
{
	//crosses�� ��q�� ������ �������� �ٰ������� ������ ����
	int crosses = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		//�� B�� ���� (p[i], p[j])�� y��ǥ ���̿� ����
		if ((p[i].y > B.y) != (p[j].y > B.y)) {
			//atX�� �� B�� ������ ���򼱰� ���� (p[i], p[j])�� ����
			double atX = (p[j].x - p[i].x)*(B.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			//atX�� ������ ���������� ������ ������ ������ ������ ������Ų��.
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
	// ���̳ʸ� �б� ���� ������ ����
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ���Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� �A��.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�.
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
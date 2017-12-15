#pragma once
#include "stdafx.h"

// 2D ���� Ŭ����
class Vector2 {
public:
	float x;	// x ��ǥ
	float y;	// y ��ǥ

				// ������
	Vector2(float x = 0, float y = 0) : x(x), y(y) {}

	// ���� ���
	float dot(const Vector2& other) const;

	// ���� ���
	// ������ ���ʹ� z��ǥ�� 0�� 3���� ���ͷ� ������ �� �ֱ� ������ 2���� ���Ϳ� ���ؼ��� ������ ������ �� �ֽ��ϴ�.
	float cross(const Vector2& other) const;

	//�������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
	float ccw(const Vector2& b);

	// ���� ���
	float length() const;

	// �Ÿ� ���
	float distance(const Vector2& other) const;

	// ����ȭ
	Vector2 normalize() const;

	// ���� �������� Ȯ��
	bool isZero() const;

	// ������ �����ε�
	Vector2& operator += (const Vector2& other) {
		return *this = *this + other;
	}

	Vector2& operator -= (const Vector2& other) {
		return *this = *this - other;
	}

	Vector2& operator *= (float scalar) {
		return *this = *this * scalar;
	}

	Vector2& operator /= (float scalar) {
		return *this = *this / scalar;
	}

	const Vector2 operator + (const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

	const Vector2 operator - (const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	}

	const Vector2 operator * (float scalar) const {
		return Vector2(x * scalar, y * scalar);
	}

	const Vector2 operator / (float scalar) const {
		return Vector2(x / scalar, y / scalar);
	}

	const Vector2 operator - () const {
		return Vector2(-x, -y);
	}

	bool operator == (const Vector2& other) const {
		//	return (x == other.x) && (y == other.y);
		return abs(x - other.x) < 0.000'01f
			&& abs(y - other.y) < 0.000'01f;
	}

	bool operator != (const Vector2& other) const {
		return !(*this == other);
	}

	bool operator < (const Vector2& other) const {
		if (x != other.x) return x < other.x;
		if (y != other.y) return y < other.y;
		return false;
	}

	// ���
	static const Vector2 ZERO;
	static const Vector2 LEFT;
	static const Vector2 RIGHT;
	static const Vector2 DOWN;
	static const Vector2 UP;
};
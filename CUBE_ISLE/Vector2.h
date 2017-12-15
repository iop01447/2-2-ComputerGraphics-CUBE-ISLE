#pragma once
#include "stdafx.h"

// 2D 벡터 클래스
class Vector2 {
public:
	float x;	// x 좌표
	float y;	// y 좌표

				// 생성자
	Vector2(float x = 0, float y = 0) : x(x), y(y) {}

	// 내적 계산
	float dot(const Vector2& other) const;

	// 외적 계산
	// 이차원 벡터는 z좌표가 0인 3차원 벡터로 생각할 수 있기 때문에 2차원 벡터에 대해서도 외적을 정의할 수 있습니다.
	float cross(const Vector2& other) const;

	//원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
	float ccw(const Vector2& b);

	// 길이 계산
	float length() const;

	// 거리 계산
	float distance(const Vector2& other) const;

	// 정규화
	Vector2 normalize() const;

	// 제로 벡터인지 확인
	bool isZero() const;

	// 연산자 오버로드
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

	// 상수
	static const Vector2 ZERO;
	static const Vector2 LEFT;
	static const Vector2 RIGHT;
	static const Vector2 DOWN;
	static const Vector2 UP;
};
#include "stdafx.h"
#include "Vector2.h"

// 내적 계산
float Vector2::dot(const Vector2& other) const {
	return (x*other.x) + (y*other.y);
}

// 외적 계산
// 이차원 벡터는 z좌표가 0인 3차원 벡터로 생각할 수 있기 때문에 2차원 벡터에 대해서도 외적을 정의할 수 있습니다.
float Vector2::cross(const Vector2& other) const {
	return(x*other.y) - (y*other.x);
}

//원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
float Vector2::ccw(const Vector2& b) {
	return this->cross(b);
}

// 길이 계산
float Vector2::length() const {
	return std::sqrt(dot(*this));
}

// 거리 계산
float Vector2::distance(const Vector2& other) const {
	return std::sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

// 정규화
Vector2 Vector2::normalize() const {
	const float len = length();
	if (len < FLT_EPSILON)
		return Vector2::ZERO;
	return *this / len;
}

// 제로 벡터인지 확인
bool Vector2::isZero() const {
	return *this == Vector2::ZERO;
}

// 상수의 값(cpp 파일에 작성)
const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::LEFT(-1.0f, 0.0f);
const Vector2 Vector2::RIGHT(1.0f, 0.0f);
const Vector2 Vector2::UP(0.0f, -1.0f);
const Vector2 Vector2::DOWN(0.0f, 1.0f);
